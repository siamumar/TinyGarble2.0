#ifndef PROGRAM_INTERFACE_EVAL_H
#define PROGRAM_INTERFACE_EVAL_H

#include "tinygarble/program_interface.h"
#include "exec/exec_common.h"

void unit_eval(auto TGPI, uint64_t bits, uint64_t num_eval) {
	emp::Timer T;
	uint64_t dc;
	double dt;

	int64_t a = rand_L_U(), b = rand_L_U();
	
	auto a_x = TGPI->TG_int_init(ALICE, bits, a);
	auto b_x = TGPI->TG_int_init(BOB, bits, b);	
	
	TGPI->gen_input_labels();
	
	TGPI->retrieve_input_labels(a_x, ALICE, bits);
	TGPI->retrieve_input_labels(b_x, BOB, bits);

	auto res_x = TGPI->TG_int(bits);

	T.start();
	for (uint64_t k = 0; k < num_eval; ++k){
		uint64_t c = rand_L_U();
		TGPI->add(res_x, a_x, c, bits);
	}
	T.get(dc, dt);
	cout << "addition with public:\t\t" << (double) dt/num_eval << " ms" << endl;

	T.start();
	for (uint64_t k = 0; k < num_eval; ++k){
		TGPI->add(res_x, a_x, b_x, bits);
	}
	T.get(dc, dt);
	cout << "addition with secret:\t\t" << (double) dt/num_eval << " ms" << endl;

	T.start();
	for (uint64_t k = 0; k < num_eval; ++k){
		uint64_t c = rand_L_U();
		TGPI->mult(res_x, a_x, c, bits);
	}
	T.get(dc, dt);
	cout << "multiplication by public:\t\t" << (double) dt/num_eval << " ms" << endl;

	T.start();
	for (uint64_t k = 0; k < num_eval; ++k){
		TGPI->mult(res_x, a_x, b_x, bits);
	}
	T.get(dc, dt);
	cout << "multiplication by secret:\t\t" << (double) dt/num_eval << " ms" << endl;

	T.start();
	for (uint64_t k = 0; k < num_eval; ++k){
		TGPI->div(res_x, a_x, b_x, bits);
	}
	T.get(dc, dt);
	cout << "division by secret:\t\t" << (double) dt/num_eval << " ms" << endl;

	TGPI->clear_TG_int (a_x);
	TGPI->clear_TG_int (b_x);
	TGPI->clear_TG_int (res_x);
	
	delete TGPI;

	return;
}

#endif //PROGRAM_INTERFACE_EVAL_H
