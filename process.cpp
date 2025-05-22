void process() {
    std::ifstream fin("build/results.txt");
    if (!fin) {
        std::cerr << "Не удалось открыть файл results.txt" << std::endl;
        return;
    }
    std::vector<double> layers, radii;
    int nLayers;
    double radius;
    while (fin >> nLayers >> radius) {
        layers.push_back(nLayers);
        radii.push_back(radius);
    }
    fin.close();
    if (layers.empty()) {
        std::cerr << "Данные не найдены в файле." << std::endl;
        return;
    }
    int N = layers.size();
    TGraph *gr = new TGraph(N, layers.data(), radii.data());
    gr->SetTitle("Moliere radius vs Number of Layers;Number of Layers;Moliere Radius (mm)");
    gr->SetMarkerStyle(20);
    gr->Draw("ALP");
}
