#pragma once

#include "STLIncludes.hpp"

namespace Causal
{
   template< class key_type, class EventPolicy >
      class Continuum : private EventPolicy
   {
      public:
         // -- Types --
         typedef key_type kind;
         typedef kind const& kind_cref;
         typedef typename EventPolicy::base_type event;
         typedef event const* event_cptr;
         typedef event const& event_cref;
         typedef std::function< void (event_cref) > dependence;

      private:
         typedef std::list<dependence> dependence_list;
         typedef std::map<kind, dependence_list> container_type;
         typedef std::pair<kind, event_cptr> causal_pair;

      public:
         class Relationship
         {
            private:
               dependence_list* List_;
               typename dependence_list::const_iterator Iter_;

            public:
               Relationship() : List_( nullptr ) {
               }

               Relationship( dependence_list& dl, typename dependence_list::const_iterator iter ) :
               List_( &dl ),
               Iter_( iter ) {
               }

               void Unmake() {
                  List_->erase( Iter_ );
               }
         };

         typedef std::forward_list<Relationship> RelationshipList;

         class Relations
         {
            private:
               RelationshipList Relations_;

            public:
               ~Relations() {
                  assert( Relations_.empty() );
               }

               void operator +=( Relationship const & r ) {
                  Relations_.push_front( r );
               }

               void Unmake() {
                  std::for_each( Relations_.begin(), Relations_.end(), []( Relationship& ri ) { ri.Unmake(); }
                  );
                  Relations_.clear();
               }
         };

      private:
         // -- Members --
         container_type Dependencies_;
         std::list<causal_pair> Events_;

      public:
         // -- Constructor / Destructor --
         Continuum() {
         }

         ~Continuum() {
            Dependencies_.clear();
            for each( auto cp in Events_ )
                  delete cp.second;
         }

         // -- Connect / Disconnect Listeners --
         Relationship Relate( kind_cref key, std::function< void (void) > const& dep ) {
            // create the intermediate function to eat the event
            typedef std::function<void (void)> void_dependance;
            std::function<void (event_cref, void_dependance const & d)> id = [&] (event_cref /* e */, void_dependance const & d) { d(); };
            auto d = std::bind( id, _1, dep );

            // insert it into the dependences
            dependence_list& dl = Dependencies_[key];
            dl.push_back( d );

            return Relationship( dl, --dl.cend() );
         }

         template< typename T >
         Relationship Relate( kind_cref key, void (*dep)( T const& ) ) {
            return Relate( key, std::function<void (T const&)>( dep ) );
         }

         template< typename T >
         Relationship Relate( kind_cref key, std::function<void (T const&)> const& dep ) {
            // generate the up-casting function
            typedef std::function<void (T const &)> higher_dependence;
            std::function<void (event_cref, higher_dependence const & d)> id = [&](event_cref e, higher_dependence const& d) { d( this->event_cast<T>(e) ); };
            auto d = std::bind( id, _1, dep );

            // insert it into the dependencies
            dependence_list& dl = Dependencies_[key];
            dl.push_back(d);

            return(Relationship(dl, --dl.cend()));
         }

         template <>                              // specialized Relate, no need to generate the intermediate casting function
         Relationship Relate(kind_cref key, std::function<void (event_cref)> const & dep) {
            dependence_list & dl = Dependencies_[key];
            dl.push_back(dep);
            return (Relationship(dl, --dl.cend()));
         }

         // -- Fire / Queue Events --
         void Enact(kind_cref key) {              // - Fires a null event
            Enact(key, event());
         }

         void Enact(kind_cref key, event_cref e) {// - Fires an event immediately
            dependence_list const & dl = Dependencies_[key];
            for each(auto d in dl)
                  d(e);
         }

                                                  // - Posts an event into the event queue
         void Fortell(kind_cref key, event_cptr e) {
            Events_.push_back(std::make_pair(key, e));
         }

         // -- Update --
         void Evolve() {
            for each(causal_pair const & cp in Events_) {
               dependence_list const & dl = Dependencies_[cp.first];
               event_cref e = *cp.second;

               for each(auto d in dl)
                     d(e);

               delete cp.second;
            }

            Events_.clear();
         }
   };

   // -- Event policies --

   class Event {};

   class SimpleEventPolicy
   {
      public:
         typedef Event base_type;

         template < typename T >
            static T const & event_cast(Event const & e) { return static_cast<T const &>(e); }
   };

   class BoostAnyEventPolicy
   {
      public:
         typedef boost::any base_type;

         template < typename T >
            static T event_cast(boost::any const & e) { return boost::any_cast<T>(e); }
   };
}
