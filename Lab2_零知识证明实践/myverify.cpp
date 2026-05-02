#include <fstream>
#include "common.hpp"

using namespace std;
using namespace libsnark;

int main()
{
    default_r1cs_gg_ppzksnark_pp::init_public_params();

    // 构造 public input
    protoboard<FieldT> pb = build_protoboard(3);

    // 读取 vk
    fstream f_vk("vk.raw", ios::in);

    r1cs_gg_ppzksnark_verification_key<
        default_r1cs_gg_ppzksnark_pp> vk;

    f_vk >> vk;
    f_vk.close();

    // 读取 proof
    fstream f_proof("proof.raw", ios::in);

    r1cs_gg_ppzksnark_proof<
        default_r1cs_gg_ppzksnark_pp> proof;

    f_proof >> proof;
    f_proof.close();

    bool result =
        r1cs_gg_ppzksnark_verifier_strong_IC<
            default_r1cs_gg_ppzksnark_pp>(
            vk,
            pb.primary_input(),
            proof
        );

    if(result)
        cout << "Verify Success!" << endl;
    else
        cout << "Verify Failed!" << endl;

    return 0;
}
