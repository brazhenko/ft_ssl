#ifndef TEST_H
# define TEST_H

#include <stddef.h>

static uint8_t		B0(uint8_t c)
{
	return ((((c) & (1u<<7u))>>7u));
}

static uint8_t		B1(uint8_t c)
{
	return (((c)&(1u<<6u))>>6u);
}

static uint8_t		B2(uint8_t c)
{
	return (((c)&(1u<<5u))>>5u);
}

static uint8_t		B3(uint8_t c)
{
	return (((c)&(1u<<4u))>>4u);
}

static uint8_t		B4(uint8_t c)
{
	return (((c)&(1u<<3u))>>3u);
}

static uint8_t		B5(uint8_t c)
{
	return (((c)&(1u<<2u))>>2u);
}

static uint8_t		B6(uint8_t c)
{
	return (((c)&(1u<<1u))>>1u);
}

static uint8_t		B7(uint8_t c)
{
	return (((c)&(1u<<0u))>>0u);
}

# endif
