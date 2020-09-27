//
// Created by 17641238 on 25.09.2020.
//

#ifndef FT_SSL_RSA_CONTEXT_H
#define FT_SSL_RSA_CONTEXT_H

# include <sys/syslimits.h>

# define RSA_CTX_MODE_MODULUS	0x1U
# define RSA_CTX_MODE_PUBIN		0x2U
# define RSA_CTX_MODE_PUBOUT	0x4U
# define RSA_CTX_MODE_NOOUT		0x8U
# define RSA_CTX_MODE_CHECK		0x10U
# define RSA_CTX_MODE_TEXT		0x20U

typedef struct	s_rsa_context
{
	int			input_fd;
	int			output_fd;
	unsigned	mode;
	char 		inform[64];
	char 		outform[64];
}				t_rsa_context;

t_rsa_context	*init_rsa_ctx();
void 			delete_rsa_ctx(const t_rsa_context *ctx);

t_rsa_context	*rsa_state_in(int argc, char **argv, t_rsa_context *ctx);
t_rsa_context	*rsa_state_out(int argc, char **argv, t_rsa_context *ctx);


t_rsa_context	*parse_rsa_argv(int argc, char **argv, t_rsa_context *ctx);

// https://www.openssl.org/docs/man1.0.2/man1/openssl-rsa.html
// -passin pass https://www.openssl.org/docs/man1.0.2/man1/openssl.html

// 		[-inform PEM]
// 		[-outform PEM]
//		[-in file]
// [-passin arg]
// 		[-out file]
// [-passout arg]
// [-des]
// 		[-text]				prints out the various public or private key components in plain text in addition to the encoded version.
// 		[-noout]				this option prevents output of the encoded version of the key.
// 		[-modulus]			this option prints out the value of the modulus of the key.
// 		[-check]
// 		[-pubin]
// 		[-pubout]

#endif //FT_SSL_RSA_CONTEXT_H
