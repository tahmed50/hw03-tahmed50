#include "bitFields.h"
#include <assert.h>

int getBit(int bn,unsigned long val) {
	assert(bn>=0 && bn<64);
	if (1UL<<bn & val) return 1;
	return 0;
}

void setBit(int bn,int new,unsigned long *val) {
	assert(bn>=0 && bn<64);
	if (new) (*val)|=1UL<<bn;
	else (*val)&=~(1L<<bn);
}

long getBitFld(int bs, int len, unsigned long val) {
    assert(bs >= 0 && bs < 64);
    assert(len > 0 && len <= 64);
    assert(bs + len <= 64);

    unsigned long mask = ((1UL << len) - 1);
    unsigned long extractedField = (val >> bs) & mask;
    
    unsigned long signBit = extractedField & (1UL << (len - 1));
    
    if (signBit) {
        int bitsToSignExtend = 64 - len;
        extractedField = (extractedField << bitsToSignExtend) >> bitsToSignExtend;
    }
    
    return (long)extractedField;
}
	//		check to make sure bs is a valid bit position in long (you may assert this is true)
	//		check to make sure len is a valid length for a subfield that starts at bs (you may assert this is true)

	// 		perform an unsigned getBitFldU to extract the unsigned version of the field
	//		get the high order bit of the result... that's the "sign" bit
	//		if the sign bit not zero, replace the 0 padding with 1 padding
	// replace this with the correct code}

unsigned long getBitFldU(int bs,int len,unsigned long val) {
	assert(bs >= 0 && bs < 64);
    assert(len > 0 && len <= 64);
    assert(bs + len <= 64);
	// TODO:
	//		check to make sure bs is a valid bit position in long (you may assert this is true)
	//		check to make sure len is a valid length for a subfield that starts at bs (you may assert this is true)

	unsigned long mask = (1UL << len) - 1;
	unsigned long extractedField = (val >> bs) & mask;
	return extractedField;

	// 		make a mask that has len 1's
	// 		Shift that mask left so it's leftmost 1 starts at bs


	//      bitwise and the mask and val to isolate the bit field bits
	//		Shift the result to the right so that the rightmost bit of the bit field is bit 0
	//			Note that shift right pads to the left with the sign bit if the field is signed, but
	//			for unsigned, it will pad to the left with 0
	return 0; // replace this with the correct code
}

void setBitFld(int bs,int len,unsigned long new,unsigned long *val) {
	assert(bs >= 0 && bs < 64);
    assert(len > 0 && len <= 64);
    assert(bs + len <= 64);

    unsigned long mask = (1UL << len) - 1;

    new = new & mask;
    new = new << bs;
    mask = mask << bs;
    *val = *val & ~mask;
    *val = *val | new;
	// TODO:
	//		check to make sure bs is a valid bit position in long (you may assert this is true)
	//		check to make sure len is a valid length for a subfield that starts at bs (you may assert this is true)
	//      Make a mask that has len bits, right justified
	//		Use mask to turn off any bits to the left of the bitField values in new
	// 		Shift both the new value and the mask to the correct bit position
	//		Turn off all bits in *val under the mask by bitwise anding with ~mask
	//		Or *val with new.  (new has zeros for all non bit field positions, so won't affect val)
}
