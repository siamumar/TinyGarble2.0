#include <emp-tool/emp-tool.h>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include "tinygarble/program_interface.h"
#include "tinygarble/program_interface_sh.h"
#include "tinygarble/TinyGarble_config.h"

using namespace std;
namespace po = boost::program_options;

void mxm(auto TGPI, int dim){

	memMeter M;
	Timer T;	
	T.start();

	uint64_t bit_width = 64;

    auto A = make_vector<int64_t>(dim, dim);
    auto B = make_vector<int64_t>(dim, dim);
	fill(A.begin(), A.end(), vector<int64_t>(dim, 1)); 
	fill(B.begin(), B.end(), vector<int64_t>(dim, -1)); 
	
	auto A_x = TGPI->TG_int_init(ALICE, bit_width, A, dim, dim);
	auto B_x = TGPI->TG_int_init(BOB, bit_width, B, dim, dim);

    TGPI->gen_input_labels();

    TGPI->retrieve_input_vector_labels(A_x, ALICE, bit_width, dim, dim);
    TGPI->retrieve_input_vector_labels(B_x, BOB, bit_width, dim, dim);

	auto C_x = TGPI->TG_int(bit_width, dim, dim);
    TGPI->mat_mult(dim, dim, dim, A_x, B_x, C_x, 0, bit_width, bit_width, bit_width, bit_width);
	
	auto C_chk = make_vector<int64_t>(dim, dim);
	TGPI->reveal_vector(C_chk, C_x, bit_width, dim, dim);	

	cout << C_chk << endl;

	T.print("mxm");
	M.print("mxm");

	delete TGPI;
}

int main(int argc, char** argv) {
	int party = 1, port = 1234;
	string netlist_address;
	string server_ip;
	int bs_mal = 10000;
	int dim;
	
	po::options_description desc{"Yao's Millionair's Problem \nAllowed options"};
	desc.add_options()  //
	("help,h", "produce help message")  //
	("party,k", po::value<int>(&party)->default_value(1), "party id: 1 for garbler, 2 for evaluator")  //
	("port,p", po::value<int>(&port)->default_value(1234), "socket port")  //
	("server_ip,s", po::value<string>(&server_ip)->default_value("127.0.0.1"), "server's IP.")  //
	("batch_size,b", po::value<int>(&bs_mal)->default_value(100000),"pre-processing bacth size for malicious setting\n\
	default:choose adaptively\nused for setting maximum available memory") //
	("sh", "semi-honest setting (default is malicious)")  //
	("dim,d", po::value<int>(&dim)->default_value(10), "square matrix dimension.");
	
	po::variables_map vm;
	try {
		po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
		po::store(parsed, vm);
		if (vm.count("help")) {
			cout << desc << endl;
			return 0;
		}
		po::notify(vm);
	}catch (po::error& e) {
		cout << "ERROR: " << e.what() << endl << endl;
		cout << desc << endl;
		return -1;
	}
		
	NetIO* io = new NetIO(party==ALICE ? nullptr:server_ip.c_str(), port, true);
	io->set_nodelay();
	
	TinyGarblePI_SH* TGPI_SH;
	TinyGarblePI* TGPI; 
	
	if (vm.count("sh")){
		cout << "Matrix Mult in semi-honest setting" << endl;
		TGPI_SH = new TinyGarblePI_SH(io, party);
		io->flush();
		mxm(TGPI_SH, dim);		
	}
	else {
		cout << "Matrix Mult in malicious setting" << endl;
		TGPI = new TinyGarblePI(io, party, bs_mal, bs_mal);
		io->flush();
		mxm(TGPI, dim);
	}
	
	delete io;
	
	return 0;
}
