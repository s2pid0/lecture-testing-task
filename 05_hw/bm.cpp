#include <benchmark/benchmark.h>
#include "stack.h" 

class StackBench : public benchmark::Fixture
{
    void SetUp(::benchmark::State& state)
    {
        stack = new Stack();
    }

    void TearDown(::benchmark::State& state)
    {
        delete stack;
    }

public:
    Stack* stack;
};

BENCHMARK_DEFINE_F(StackBench, PushBench)(benchmark::State& st)
{
    for (auto _ : st)
    {
        for (int i = 0; i < st.range(0); i++)
            push(stack, i);
    }
}

BENCHMARK_DEFINE_F(StackBench, PopBench)(benchmark::State& st)
{
    for (int i = 0; i < st.range(0); i++)
        push(stack, i);

    for (auto _ : st)
    {
        for (int i = 0; i < st.range(0); i++)
            pop(stack);
    }
}

BENCHMARK_REGISTER_F(StackBench, PushBench)
->Arg(100)
->Arg(1000)
->Arg(10000)
->Arg(100000)
->Arg(1000000);

BENCHMARK_REGISTER_F(StackBench, PopBench)
->Arg(100)
->Arg(1000)
->Arg(10000)
->Arg(100000)
->Arg(1000000);

BENCHMARK_MAIN();
