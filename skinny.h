/**
 * Implement the following API.
 * You can add your own functions above, but don't modify below this line.
 */

/**
 * SKINNY-128-384 block cipher encryption.
 * Under 48-byte tweakey at k, encrypt 16-byte plaintext at p and store the 16-byte output at c.
 */
void skinny(unsigned char *c, const unsigned char *p, const unsigned char *k);
void subCells(unsigned char *subP);
void addConstant(unsigned char *subP, unsigned int i);
void addTweakey(unsigned char *subP, unsigned char *tk1, unsigned char *tk2, unsigned char *tk3);
void shiftRows(unsigned char *subP);
void mixColumns(unsigned char *subP);