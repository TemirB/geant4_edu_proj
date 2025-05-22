#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cmath>

#include <TGraphErrors.h>
#include <TCanvas.h>

struct Point {double x, y, err; };

int main() {
    std::ifstream list("../build/results/output.list");
    if (!list) {
        std::cerr << "Cannot open ../build/results/output.list" << std::endl;
        return 1;
    }
    std::vector<std::string> filenames;
    std::string line;
    while (std::getline(list, line)) {
        if (!line.empty()) filenames.push_back(line);
    }

    std::vector<Point> points;

    for (const auto& filename : filenames) {
        Point point;
        int nLayers = -1;
        size_t pos1 = filename.find("rm_vs_layers_");
        size_t pos2 = filename.find(".txt", pos1);
        if (pos1 != std::string::npos && pos2 != std::string::npos && (pos1 + 13) <= pos2) {
            std::string nstr = filename.substr(pos1 + 13, pos2 - (pos1 + 13));
            try {
                nLayers = std::stoi(nstr);
                point.x = nLayers;
            } catch (const std::exception& e) {
                std::cerr << "Ошибка в имени файла: " << filename << std::endl;
                continue;
            }
        } else {
            std::cerr << "Неверный формат имени файла: " << filename << std::endl;
            continue;
        }

        std::ifstream in(filename);
        std::vector<double> radii;
        double mean = 0;
        double variation = 0;
        double r = 0;
        double stdev = 0;
        std::string s;

        while (std::getline(in, s)) {
            if (s.empty() || s[0] == '#') continue;
            std::istringstream iss(s);
            if (iss >> r) {
                radii.push_back(r);
                mean += r;
            }
        }
        if (radii.empty()) {
            std::cerr << "Файл " << filename << " пустой или некорректный\n";
            continue;
        }
        mean /= radii.size();

        for (auto R : radii) {
            variation += (R - mean) * (R - mean);
        }

        if (radii.size() > 1) {
            stdev = std::sqrt(variation / (radii.size() - 1));
        } else {
            stdev = 0.;
        }
        point.y = mean;
        point.err = stdev;
        points.push_back(point);
    }

    std::sort(points.begin(), points.end(), [](Point a, Point b){ return a.x < b.x; });
    TGraphErrors* graph = new TGraphErrors(points.size());
    for (int i = 0; i < points.size(); i++) {
        graph->SetPoint(i, points[i].x, points[i].y);
        graph->SetPointError(i, 0, points[i].err);
    }

    graph->SetMarkerStyle(21);
    graph->SetLineColor(kRed);
    graph->SetMarkerSize(1.3);
    graph->SetLineWidth(2);
    graph->SetMinimum(8);
    graph->SetMaximum(16);
    graph->SetTitle("Moliere radius vs N of layers;Layers;Moliere radius (mm)");

    TCanvas* canvas = new TCanvas("rm_vs_layers", "Moliere radius vs N of layers; Moliere radius, (mm)", 900, 700);
    canvas->cd();
    canvas->SetGrid();     
    graph->Draw("ALP");
    
    canvas->SaveAs("result.pdf");
    return 0;
}