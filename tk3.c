#include <string.h>
#include <stdio.h>
#include "tk3.h"
#include "skinny.h"

unsigned char p[48] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* TODO */
void init(context *ctx) {
  memset(ctx->state, 0, 48);
  ctx->state[16] = 0x80;
  memset(ctx->a, 0, 256);
  ctx->len = 0;
}

/* TODO */
void update(const unsigned char *a, int len, context *ctx) {
  memcpy(ctx->a+ctx->len, a, 256-ctx->len);
  ctx->len += len;
}

/* TODO */
void finalize(unsigned char *a, context *ctx) {
  unsigned char temp[48];
  unsigned char *temp2 = ctx->state;
  unsigned char *temp3 = ctx->a;
  unsigned char temp5[32];
  memcpy(temp5, a, 32);
  while (ctx->len >= 16)
  {
    int i = 16;
    while (i > 0)
    {
      *temp2++ ^= *temp3++;
      --i;
    }
    skinny(temp, p, ctx->state);
    skinny(temp+16, p+16, ctx->state);
    skinny(temp+32, p+32, ctx->state);
    memcpy(ctx->state, temp, 48);
    *ctx->a += 16;
    ctx->len -= 16;
    temp2 = ctx->state;
  }
  int j = ctx->len;
  while (j > 0)
  {
    *temp2++ ^= *temp3++;
    --j;
  }
  temp2 = ctx->state;
  temp2[ctx->len] ^= 0x80; 
  skinny(temp, p, ctx->state);
  skinny(temp+16, p+16, ctx->state);
  skinny(temp+32, p+32, ctx->state);
  memcpy(ctx->state, temp, 48);

  unsigned char temp4[16];
  memset(temp4, 0, 16);
  skinny(temp4, p, ctx->state);
  memcpy(a, ctx->state, 16);
  memcpy(a+16, temp4, 16);

}
