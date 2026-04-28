from phe import paillier
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto. Util .Padding import pad, unpad
import random

##################### AES 加解密函数
def aes_encrypt(m, key):
    cipher = AES.new(key, AES.MODE_ECB)
    m_bytes = str(m).encode()
    return cipher . encrypt(pad(m_bytes, AES. block_size))

def aes_decrypt(c , key):
    cipher = AES.new(key, AES.MODE_ECB)
    m_bytes = unpad(cipher .decrypt(c) , AES. block_size)
    return int(m_bytes.decode())

##################### 客户端：生成密钥
public_key , private_key = paillier . generate_paillier_keypair ()
aes_key = get_random_bytes(16) # 128−bit AES 密钥
##################### 客户端：准备数据并加密上传
message_list = [100,200,300,400,500,600,700,800,900,1000]
enc_message_list = [aes_encrypt(m, aes_key) for m in message_list ]

##################### 服务器端：仅存储 AES 密文
server_data = enc_message_list.copy()
length = len(server_data)

##################### 客户端：选择查询位置
pos = random.randint(0, length-1)
print("要读取的位置：", pos)

##################### 客户端：生成同态选择向量
enc_list = []
for i in range(length):
    bit = 1 if i == pos else 0
    enc_list .append(public_key . encrypt(bit))

##################### 服务器端处理
selected_cipher = None
for i in range(length):
    if private_key. decrypt(enc_list [ i ]) == 1:
        selected_cipher = server_data[ i ]

##################### 客户端解密
result = aes_decrypt(selected_cipher , aes_key)
print("最终得到的明文：", result)
print("验证是否正确：", result == message_list[pos])