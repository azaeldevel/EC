
#ifndef OCTETOS_EC_TDD_V1_HH
#define OCTETOS_EC_TDD_V1_HH

#include <CUnit/Basic.h>

#include "../1/ec.hh"

namespace core = oct::core::v3;
namespace ec = oct::ec::v1;

    struct Single : public ec::Single<float>
    {
    public:
        typedef ec::Single<float> SINGLE_BASE;

    public:
        Single() = default;
        Single(size_t);
        Single(const core::array<float>& ins);
        Single(const core::array<float>& ins,size_t);

        void init_load_operators();
        void init_data();

        //operators maths
        void incs1();

    public:
        virtual float evaluate() const;

    public:
        core::array<float> data;
        core::array<float> paras;
        core::array<void (Single::*)()> opers;
    };


    struct Math : public Single
    {
    public:
        typedef Single SINGLE_BASE;

    public:
        Math() = default;
        Math(size_t);
        Math(const core::array<float>& ins);
        Math(const core::array<float>& ins,size_t);

    public:

    public:
    };


int v1_init(void);
int v1_clean(void);
void v1_developing();

#endif
