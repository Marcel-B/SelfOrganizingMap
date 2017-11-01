// "SelfOrganizingMapStart.cpp": Definiert den Einstiegspunkt für die Konsolenanwendung.
//
#include <som.hpp>
#include <iostream>
#include <inout.h>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <set.h>
#include <sstream>

int main(int argc, char *argv[])
{
	for (size_t i = 0; i < argc; ++i)
		std::cout << argv[i] << std::endl;
	std::string validation_data = "test.set";
	std::vector<std::vector<double>> scaled_data;
	auto set = new com_b_velop::Set();

	com_b_velop::InOut::import_data("copy.csv", set);
	scaled_data.clear();
	auto split_set = set->SplitValues(30);

	// Erst mal wegspeichern
	delete split_set->SaveSet(validation_data.c_str());
	auto som = new com_b_velop::Som(70, 30, set->cols);
	som->SetIterationMax(15);
	som->SetTrainData(set)->StartTraining();
	auto tmp_set = com_b_velop::Set::OpenSet(validation_data.c_str());
	tmp_set->features = set->features;
	const auto validation = som->Validation(tmp_set);
	auto valid_set = validation.valid_set;

	std::ofstream ofs("table1.csv", std::ios::out);
	std::ofstream oofs("table2.csv");
	std::ofstream del("delta.csv");
	std::stringstream strst;
	std::string tmp;
	int idx;
	ofs << set->features[0].name;
	oofs << set->features[0].name;
	del << set->features[0].name;
	for (size_t j = 1; j < valid_set[0].out.size(); ++j)
	{
		ofs << ';' << set->features[j].name;
		oofs << ';' << set->features[j].name;
		del << ';' << set->features[j].name;
	}
	ofs << std::endl;
	oofs << std::endl;
	del << std::endl;
	for (size_t i = 0; i < valid_set.size(); ++i)
	{
		//    cout << setw(8) << valid_set[i].d << " | BMU[" << valid_set[i].x << "][" << valid_set[i].y << "]" << endl;
		tmp = std::to_string(valid_set[i].out[0]);
		idx = tmp.find('.');
		if (idx >= 0)
			tmp[idx] = ',';
		tmp.erase(tmp.find_last_not_of('0') + 1, std::string::npos);
		for (size_t j = 1; j < valid_set[i].out.size(); ++j)
		{
			tmp = std::to_string(valid_set[i].out[j]);
			idx = tmp.find('.');
			if (idx >= 0)
				tmp[idx] = ',';
			tmp.erase(tmp.find_last_not_of('0') + 1, std::string::npos);
			ofs << ';' << tmp;
		}
		ofs << std::endl;


		tmp = std::to_string(valid_set[i].in[0]);
		idx = tmp.find('.');
		if (idx >= 0)
			tmp[idx] = ',';

		tmp.erase(tmp.find_last_not_of('0') + 1, std::string::npos);

		oofs << tmp;
		for (size_t j = 1; j < valid_set[i].in.size(); ++j)
		{
			tmp = std::to_string(valid_set[i].in[j]);
			idx = tmp.find('.');
			if (idx >= 0)
				tmp[idx] = ',';
			tmp.erase(tmp.find_last_not_of('0') + 1, std::string::npos);
			oofs << ';' << tmp;
		}
		oofs << std::endl;

		tmp = std::to_string(valid_set[i].delta[0]);
		idx = tmp.find('.');
		if (idx >= 0)
			tmp[idx] = ',';
		tmp.erase(tmp.find_last_not_of('0') + 1, std::string::npos);

		del << tmp;
		for (size_t j = 1; j < valid_set[i].in.size(); ++j)
		{
			tmp = std::to_string(valid_set[i].delta[j]);
			idx = tmp.find('.');
			if (idx >= 0)
				tmp[idx] = ',';
			tmp.erase(tmp.find_last_not_of('0') + 1, std::string::npos);
			del << ';' << tmp;
		}
		del << std::endl;
	}
	del.close();
	oofs.close();
	ofs.close();

	std::cout << std::setw(22) << std::setfill(' ') << std::left << "Init ready" << std::endl;

	delete som;
	return 0;
}


