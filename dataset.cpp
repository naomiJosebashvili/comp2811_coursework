// COMP2811 Coursework 1: QuakeDataset class

#include "dataset.hpp"
#include <stdexcept>
#include "csv.hpp"

void QuakeDataset::loadData(const std::string& filename) {
    csv::CSVReader reader(filename);

    for (auto& row: reader) {
        std::string time = row["time"].get<>();
        double latitude = row["latitude"].get<double>();
        double longitude = row["longitude"].get<double>();
        double depth = row["depth"].get<double>();
        double mag = row["mag"].get<double>();

        data.push_back(Quake(time, latitude, longitude, depth, mag));
    }
}

Quake QuakeDataset::strongest() const {
    if (data.size() == 0) {
        throw std::runtime_error("The data set is empty");
    }
    Quake strongest = data[0];
    for (Quake quake : data) {
        if (quake.getMagnitude() > strongest.getMagnitude()) {
            strongest = quake;
        }
    }
    return strongest;
}

Quake QuakeDataset::shallowest() const {
    if (data.size() == 0) {
        throw std::runtime_error("The data set is empty");
    }
    Quake shallowest = data[0];
    for (Quake quake : data) {
        if (quake.getDepth() < shallowest.getDepth()) {
            shallowest = quake;
        }
    }
    return shallowest;
}

double QuakeDataset::meanDepth() const {
    if (data.size() == 0) {
        throw std::runtime_error("The data set is empty");
    }
    double totalDepth = 0.0;
    for (Quake quake : data) {
        totalDepth += quake.getDepth();
    }
    return totalDepth / data.size();
}

double QuakeDataset::meanMagnitude() const {
    if (data.size() == 0) {
        throw std::runtime_error("The data set is empty");
    }
    double totalMagnitude = 0.0;
    for (Quake quake : data) {
        totalMagnitude += quake.getMagnitude();
    }
    return totalMagnitude / data.size();
}