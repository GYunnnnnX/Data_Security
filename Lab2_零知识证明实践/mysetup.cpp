#include <fstream>
#include "common.hpp"

using namespace std;
using namespace libsnark;

int main()
{
    default_r1cs_gg_ppzksnark_pp::init_public_params();

    // 这里只是构造约束系统
    protoboard<FieldT> pb = build_protoboard(3);

    const r1cs_constraint_system<FieldT> constraint_system =
        pb.get_constraint_system();

    cout << "Generating keypair..." << endl;

    auto keypair =
        r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(
            constraint_system
        );

    // 保存 proving key
    fstream f_pk("pk.raw", ios::out);
    f_pk << keypair.pk;
    f_pk.close();

    // 保存 verification key
    fstream f_vk("vk.raw", ios::out);
    f_vk << keypair.vk;
    f_vk.close();

    cout << "Setup finished." << endl;

    return 0;
}
