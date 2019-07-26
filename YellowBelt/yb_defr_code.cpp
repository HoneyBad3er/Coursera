#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	string responce_type;
	is >> responce_type;

	if(responce_type == "NEW_BUS")
		q.type = QueryType::NewBus;
	if(responce_type == "BUSES_FOR_STOP")
		q.type = QueryType::BusesForStop;
	if(responce_type == "STOPS_FOR_BUS")
		q.type = QueryType::StopsForBus;
	if(responce_type == "ALL_BUSES")
		q.type = QueryType::AllBuses;


	switch (q.type) {

	case QueryType::NewBus:
		is >> q.bus;
		int stop_count;
		is >> stop_count;
		q.stops.resize(stop_count);
		for (int i = 0; i < stop_count; ++i){
			is >> q.stops[i];
		}
		break;

	case QueryType::BusesForStop:
		is >> q.stop;
		break;

	case QueryType::StopsForBus:
		is >> q.bus;
		break;

	case QueryType::AllBuses:
		break;

	}

	return is;
}

struct BusesForStopResponse {
	bool empty;
	string stop;
	vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (r.empty) {
		cout << "No stop" << endl;
	}
	else {
		for (const string& bus : r.buses) {
			cout << bus << " ";
		}
		cout << endl;
	}
	return os;
}

struct StopsForBusResponse {
	bool empty;
	string bus;
	map<string,vector<string>> stops_to_buses;
	vector<string> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (r.empty) {
		cout << "No bus" << endl;
	}
	else {
		for (const string& stop : r.stops) {
			cout << "Stop " << stop << ": ";
			if (r.stops_to_buses.at(stop).size() == 1) {
				cout << "no interchange";
			}
			else {
				for (const string& other_bus : r.stops_to_buses.at(stop)) {
					if (r.bus != other_bus) {
						cout << other_bus << " ";
					}
				}
			}
			cout << endl;
		}
	return os;
}
	return os;
}

struct AllBusesResponse {
	map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r){
	if (r.buses_to_stops.empty()) {
		cout << "No buses" << endl;
	}
	else {
		for (const auto& bus_item : r.buses_to_stops) {
			cout << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				cout << stop << " ";
			}
			cout << endl;
		}
	}
	return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		buses_to_stops[bus] = stops;
		for (string stop : stops) {
			stops_to_buses[stop].push_back(bus);
		}
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		BusesForStopResponse responce;
		responce.stop = stop;
		if (stops_to_buses.count(stop) == 0){
			responce.empty = true;
		}
		else{
			responce.empty = false;
			responce.buses = stops_to_buses.at(stop);
		}
		return responce;
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		StopsForBusResponse responce;
		responce.bus = bus;
		if(buses_to_stops.count(bus) == 0){
			responce.empty = true;
		}
		else{
			responce.empty = false;
			responce.stops = buses_to_stops.at(bus);
			responce.stops_to_buses = stops_to_buses;
		}
		return responce;
	}

	AllBusesResponse GetAllBuses() const {
		AllBusesResponse responce;

		responce.buses_to_stops = buses_to_stops;

		return responce;
	}

private:
	map<string, vector<string>> buses_to_stops, stops_to_buses;
};



int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}

	return 0;
}
