#ifndef COMMON_HPP
#define COMMON_HPP

#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>
#include <libsnark/gadgetlib1/protoboard.hpp>

using namespace libsnark;
using namespace std;

// 有限域
typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;

// 构造电路
protoboard<FieldT> build_protoboard(int x_value)
{
    default_r1cs_gg_ppzksnark_pp::init_public_params();

    protoboard<FieldT> pb;

    // 定义变量
    pb_variable<FieldT> out;
    pb_variable<FieldT> x;
    pb_variable<FieldT> w1;   // x^2
    pb_variable<FieldT> w2;   // x^3

    // allocate
    out.allocate(pb, "out");
    x.allocate(pb, "x");
    w1.allocate(pb, "w1");
    w2.allocate(pb, "w2");

    // out 是 public input
    pb.set_input_sizes(1);

    // 设置 witness
    pb.val(x) = x_value;
    pb.val(w1) = x_value * x_value;
    pb.val(w2) = x_value * x_value * x_value;
    pb.val(out) = 35;

    // 添加约束
    // w1 = x*x
    pb.add_r1cs_constraint(
        r1cs_constraint<FieldT>(x, x, w1)
    );

    // w2 = w1*x
    pb.add_r1cs_constraint(
        r1cs_constraint<FieldT>(w1, x, w2)
    );

    // out = w2 + x + 5
    pb.add_r1cs_constraint(
        r1cs_constraint<FieldT>(
            1,
            w2 + x + FieldT(5),
            out
        )
    );

    return pb;
}

#endif
