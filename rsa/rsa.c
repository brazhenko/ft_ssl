//
// Created by 17641238 on 25.09.2020.
//

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "rsa_context.h"
#include "rsa.h"
#include "utilities.h"
#include <unistd.h>
#include "key_io.h"

# define STRING1	"RSA Private-Key: (64 bit)\n"
# define STRING2	"modulus: "
# define STRING3	"publicExponent: "
# define STRING4	"privateExponent: "
# define STRING5	"prime1: "
# define STRING6	"prime2: "
# define STRING7	"exponent1: "
# define STRING8	"exponent2: "
# define STRING9	"coefficient: "
# define STRING10	"Modulus="
# define STRING11	"Exponent: "
# define STRING12	"RSA Public-Key: (64 bit)\n"
# define STRING13	"Modulus: "

// Отрефакторить key_io!											V
// Пофиксить размерность ключа, возможно просто подбором, лол		V
// Написать полные тесты на genrsa, rsa								V
// расширенный алгос евклида расшарить
// МТФ
// надо проверки возвратов говнометодов сделать и выход по eггor



void parse_key(t_rsa_context *ctx,
		t_rsa_pub_key *pub_out,
		t_rsa_priv_key *priv_out)
{
	if (ctx->mode & RSA_CTX_MODE_PUBIN)
	{
		if (strcmp(ctx->inform, "PEM") == 0)
			rsa_parse_pub_pem(ctx->input_fd, pub_out);
		else if (strcmp(ctx->inform, "DER") == 0)
			rsa_parse_pub_der(ctx->input_fd, pub_out);
		else
		{
			nstrprinterror(1, "Unknown -inform param\n");
			exit(1);
		}
	}
	else
	{
		if (strcmp(ctx->inform, "PEM") == 0)
			rsa_parse_priv_pem(ctx->input_fd, priv_out);
		else if (strcmp(ctx->inform, "DER") == 0)
			rsa_parse_priv_der(ctx->input_fd, priv_out);
		else
		{
			nstrprinterror(1, "Unknown -inform param\n");
			exit(1);
		}
	}
}

void generate_out_key(t_rsa_context *ctx,
		t_rsa_pub_key *pub_out,
		t_rsa_priv_key *priv_out)
{
	if (!(ctx->mode & RSA_CTX_MODE_PUBIN))
	{
		pub_out->n = priv_out->n;
		pub_out->e = priv_out->e;
	}
}

void int128tohex(__int128 in, char *out, const char *alphabet)
{
	char *out_copy;
	char c;
	char tmp;

	if (in == 0)
	{
		*out = '0';
		return;
	}
	out_copy = out;
	while (in)
	{
		tmp = (char)(in % 16);
		*out = alphabet[tmp];
		out++;
		in /= 16;
	}
	out--;
	while (out_copy < out)
	{
		c = *out_copy;
		*out_copy = *out;
		*out = c;
		out_copy++;
		out--;
	}
}

void 	print_modulus(t_rsa_context *ctx, __int128 modulus)
{
	char 	out[128];

	memset(out, 0, sizeof(out));
	strcat(out, STRING10);
	int128tohex(modulus, &out[0] + strlen(out), "0123456789ABCDEF");
	strcat(out, "\n");
	write(ctx->output_fd, out, strlen(out));
}

void 	print_priv_key(t_rsa_context *ctx, t_rsa_priv_key *k)
{
	if (strcmp(ctx->outform, "DER") == 0)
		rsa_put_priv_der(ctx->output_fd, k);
	else if (strcmp(ctx->outform, "PEM") == 0)
		rsa_put_priv_pem(ctx->output_fd, k);
	else
	{
		nstrprinterror(1, "Unknown outform, exit\n");
		exit(1);
	}
}

void 	print_pub_key(t_rsa_context *ctx, const t_rsa_pub_key *k)
{
	if (strcmp(ctx->outform, "DER") == 0)
		rsa_put_pub_der(ctx->output_fd, k);
	else if (strcmp(ctx->outform, "PEM") == 0)
		rsa_put_pub_pem(ctx->output_fd, k);
	else
	{
		nstrprinterror(1, "Unknown outform, exit\n");
		exit(1);
	}
}

void int128toa(__int128 in, char *out)
{
	char *out_copy;
	char c;

	if (in == 0)
	{
		*out = '0';
		return;
	}
	out_copy = out;
	while (in)
	{
		*out = (char)((in % 10) + '0');
		out++;
		in /= 10;
	}
	out--;
	while (out_copy < out)
	{
		c = *out_copy;
		*out_copy = *out;
		*out = c;
		out_copy++;
		out--;
	}

}

static void append_text_int_with_new_line(char *out, __int128 num)
{
	// some tests
	{
		{
			char ar[128]={0};
			__int128 a = 1234123;
			int128toa(a, ar);
			assert(strcmp(ar, "1234123") == 0);
		}
		{
			char ar[128]={0};
			__int128 a = 0;
			int128toa(a, ar);
			assert(strcmp(ar, "0") == 0);
		}
		{
			char ar[128]={0};
			__int128 a = 1234512523541;
			int128toa(a, ar);
			assert(strcmp(ar, "1234512523541") == 0);
		}
		{
			char ar[128]={0};
			__int128 a = 1235124361999999;
			int128toa(a, ar);
			assert(strcmp(ar, "1235124361999999") == 0);
		}
		////////// hex test ////////////
		{
			char ar[128]={0};
			__int128 a = 3623653217;
			int128tohex(a, ar, "0123456789abcdef");
			assert(strcmp(ar, "d7fc8f61") == 0);
		}
		{
			char ar[128]={0};
			__int128 a = 3371369363;
			int128tohex(a, ar, "0123456789abcdef");
			assert(strcmp(ar, "c8f30393") == 0);
		}
	}
	char 	arr[128];

	memset(arr, 0, sizeof(arr));
	int128toa(num, arr);
	strcat(arr, " (0x");
	int128tohex(num, &arr[0] + strlen(arr), "0123456789abcdef");
	strcat(arr, ")\n");
	strcat(out, arr);
}

void	print_text_pub_key(t_rsa_context *ctx, t_rsa_pub_key *k)
{
	char 	to_print[2048];

	memset(to_print, 0, sizeof(to_print));
	strcat(to_print, STRING12);

	strcat(to_print, STRING13);
	append_text_int_with_new_line(to_print, k->n);
	strcat(to_print, STRING11);
	append_text_int_with_new_line(to_print, k->e);
	write(ctx->output_fd, to_print, strlen(to_print));
}

void	print_text_priv_key(t_rsa_context *ctx, t_rsa_priv_key *k)
{
	char 	to_print[2048];

	memset(to_print, 0, sizeof(to_print));
	strcat(to_print, STRING1);
	strcat(to_print, STRING2);
	append_text_int_with_new_line(to_print, k->n);
	strcat(to_print, STRING3);
	append_text_int_with_new_line(to_print, k->e);
	strcat(to_print, STRING4);
	append_text_int_with_new_line(to_print, k->d);
	strcat(to_print, STRING5);
	append_text_int_with_new_line(to_print, k->p);
	strcat(to_print, STRING6);
	append_text_int_with_new_line(to_print, k->q);
	strcat(to_print, STRING7);
	append_text_int_with_new_line(to_print, k->dp);
	strcat(to_print, STRING8);
	append_text_int_with_new_line(to_print, k->dq);
	strcat(to_print, STRING9);
	append_text_int_with_new_line(to_print, k->qinv);
	write(ctx->output_fd, to_print, strlen(to_print));
}

void	process_output(t_rsa_context *ctx,
		t_rsa_pub_key *pub_out,
		t_rsa_priv_key *priv_out)
{
	if ((ctx->mode & RSA_CTX_MODE_TEXT) && (ctx->mode & RSA_CTX_MODE_PUBIN))
		print_text_pub_key(ctx, pub_out);
	if ((ctx->mode & RSA_CTX_MODE_TEXT) && !(ctx->mode & RSA_CTX_MODE_PUBIN))
		print_text_priv_key(ctx, priv_out);
	if (ctx->mode & RSA_CTX_MODE_MODULUS)
		print_modulus(ctx, ctx->mode & RSA_CTX_MODE_PUBOUT ? pub_out->n : priv_out->n);
	if (!(ctx->mode & RSA_CTX_MODE_NOOUT) && (ctx->mode & RSA_CTX_MODE_PUBOUT))
		print_pub_key(ctx, pub_out);
	if (!(ctx->mode & RSA_CTX_MODE_NOOUT) && !(ctx->mode & RSA_CTX_MODE_PUBOUT))
		print_priv_key(ctx, priv_out);
}

void	rsa(int ac, char **av)
{
	t_rsa_context *ctx;
	t_rsa_priv_key priv_key;
	t_rsa_pub_key pub_key;

	memset(&priv_key, 0, sizeof(priv_key));
	memset(&pub_key, 0, sizeof(pub_key));
	ctx = init_rsa_ctx();
	ctx = parse_rsa_argv(ac, av, ctx);

	parse_key(ctx, &pub_key, &priv_key);
	if (ctx->mode & RSA_CTX_MODE_PUBIN)
		ctx->mode |= RSA_CTX_MODE_PUBOUT;
	generate_out_key(ctx, &pub_key, &priv_key);
	process_output(ctx, &pub_key, &priv_key);
}
