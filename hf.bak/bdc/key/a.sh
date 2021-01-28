openssl genrsa -out rsa_private_key.pem 2048

openssl rsa -in rsa_private_key.pem -out key -pubout

openssl pkcs8 -topk8 -in rsa_private_key.pem -out privateKey -nocrypt
