
#include "io.h"

void PIC_IO::writeFile(std::vector<double> data){
	PIC.outfile.open("PIC" + std::to_string(PIC.step) + ".csv");
	for (double i : data){
		PIC.outfile << i << std::endl;
	}
	PIC.outfile.close();
}