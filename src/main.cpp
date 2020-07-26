#include <iostream>
#include "ap_int.h"
#include "utils/x_hls_utils.h"
#include<stdint.h>
#include "hls_stream.h"
#include "ap_axi_sdata.h"

#define CUST_DATA_MASK 0x7ff
#define POLARITY_SHIFT 11
#define POLARITY_MASK (1 << POLARITY_SHIFT)  // 1 bit at bit 11
#define POLARITY_Y_ADDR_SHIFT 22
#define POLARITY_Y_ADDR_MASK (511 << POLARITY_Y_ADDR_SHIFT) // 9 bits from bits 22 to 30
#define POLARITY_X_ADDR_SHIFT 12
#define POLARITY_X_ADDR_MASK (1023 << POLARITY_X_ADDR_SHIFT) // 10 bits from bits 12 to 21

void eventsGeneratorViaFile(
		ap_uint<64> input,
//		ap_uint<64> counterIn, ap_uint<32> *status, ap_uint<64> *counterOut,
		hls::stream< ap_uint<16> > &xStreamOut,
		hls::stream< ap_uint<16> > &yStreamOut,
		hls::stream< ap_uint<64> > &tsStreamOut,
		hls::stream< ap_uint<1> > &polStreamOut,
		hls::stream< ap_uint<16> > &custDataStreamOut
)
{
#pragma HLS INTERFACE ap_vld port=input
#pragma HLS INTERFACE s_axilite port=input bundle=config
//#pragma HLS INTERFACE s_axilite port=status bundle=config
//#pragma HLS INTERFACE s_axilite port=counterIn bundle=config

#pragma HLS INTERFACE axis register both port=custDataStreamOut
#pragma HLS INTERFACE axis register both port=tsStreamOut
#pragma HLS INTERFACE axis register both port=polStreamOut
#pragma HLS INTERFACE axis register both port=yStreamOut
#pragma HLS INTERFACE axis register both port=xStreamOut

	ap_uint<16> x, y;
	ap_uint<1> pol;
	ap_uint<16> custData;
	ap_uint<64> ts;
	ap_uint<32> retStatus = 0;

	ap_uint<64> data = input;

	x = ((data) & POLARITY_X_ADDR_MASK) >> POLARITY_X_ADDR_SHIFT;
	y = ((data) & POLARITY_Y_ADDR_MASK) >> POLARITY_Y_ADDR_SHIFT;
	pol  = ((data) & POLARITY_MASK) >> POLARITY_SHIFT;
	custData = data & CUST_DATA_MASK;
	ts = data >> 32;

	xStreamOut << x;
	yStreamOut << y;
	tsStreamOut << ts;
	polStreamOut << pol;
	custDataStreamOut << custData;

	retStatus = 1;
//	*counterOut = counterIn;
//	*status = retStatus; // Indicate that data has been sent out.
}
