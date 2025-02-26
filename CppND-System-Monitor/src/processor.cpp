#include "processor.h"
#include "linux_parser.h"

#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>



using std::string;
using std::vector;
using std::cout;
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

float Processor::Utilization() { 
  	
  	Processor processor_prev = Parsing();
  	processor_prev.total_idle = processor_prev.idle + processor_prev.iowait;
  	processor_prev.total_non_idle = processor_prev.user + processor_prev.nice + processor_prev.system + processor_prev.irq + processor_prev.softirq + processor_prev.steal;
  	processor_prev.total = processor_prev.total_idle + processor_prev.total_non_idle;
  	  	
  	
  
    Processor processor_current = Parsing();
  	processor_current.total_idle = processor_current.idle + processor_current.iowait;
  	processor_current.total_non_idle = processor_current.user + processor_current.nice + processor_current.system + processor_current.irq + processor_current.softirq + processor_current.steal;
  	processor_current.total = processor_current.total_idle + processor_current.total_non_idle;
  

  	float cpu_percentage_current =  float(processor_current.total - processor_current.total_idle) / processor_current.total; 

  	return cpu_percentage_current; }


Processor Processor::Parsing(){
	Processor processor_data;
  	string line;
   	
  	std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  	if (stream.is_open()){
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> processor_data.cpu_name>> processor_data.user >> processor_data.nice >> processor_data.system >> processor_data.idle >> processor_data.iowait >> processor_data.irq >> processor_data.softirq >> processor_data.steal;      
    }

    return processor_data;
}
