#include <fstream>
#include "common.hpp"

using namespace std;
using namespace libsnark;

int main()
{
    int x;
    cout << "Input secret x: ";
    cin >> x;

    protoboard<FieldT> pb = build_protoboard(x);

    if (!pb.is_satisfied())
    {
        cout << "Constraint not satisfied!" << endl;
        return 0;
    }

    cout << "Public input: " << pb.primary_input() << endl;
    cout << "Private input: " << pb.auxiliary_input() << endl;

    // 读取 proving key
    fstream f_pk("pk.raw", ios::in);
    r1cs_gg_ppzksnark_proving_key<
        default_r1cs_gg_ppzksnark_pp> pk;

    f_pk >> pk;
    f_pk.close();

    // 生成 proof
    auto proof =
        r1cs_gg_ppzksnark_prover<
            default_r1cs_gg_ppzksnark_pp>(
            pk,
            pb.primary_input(),
            pb.auxiliary_input()
        );

    // 保存 proof
    fstream f_proof("proof.raw", ios::out);
    f_proof << proof;
    f_proof.close();

    cout << "Proof generated successfully!" << endl;

    return 0;
}
