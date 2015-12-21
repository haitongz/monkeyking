#include <iostream>

template <typename EnumT, typename BaseEnumT>
struct InheritEnum
{
  InheritEnum() {
  }

  InheritEnum(EnumT e)
      : enum_(e) {
  }

  InheritEnum(BaseEnumT e)
      : baseEnum_(e) {
  }

  explicit InheritEnum(int val)
  : enum_(static_cast<EnumT>(val)) {
  }

  operator EnumT() const { return enum_; }

  private:
    // Note - the value is declared as a union mainly for as a debugging aid. If
    // the union is undesired and you have other methods of debugging, change it
    // to either of EnumT and do a cast for the constructor that accepts BaseEnumT.

    union {
      EnumT enum_;
      BaseEnumT baseEnum_;
    };
};

struct A {
  enum {
    _type_ = 'A'
  };

  typedef A packet_t;

  void dump() {
    std::cout << "Type is: " << _type_ << std::endl;
  }
};

struct B: public A {
  enum {
    _type_ = 'B'
  };

  typedef InheritEnum<BCONST,CONST> BEnum;

  typedef B packet_t;
};

int main() {
  A a;
  B b;

  a.dump();
  b.dump();
}
