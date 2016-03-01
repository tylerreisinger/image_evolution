#include <iostream>
#include <sstream>

#include <QApplication>

#include "gui/MainWindow.h"

#include "ImageEvolver.h"
#include "Image.h"

int qt_main(int argc, char** argv) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

int cmd_main(int argc, char** argv) {
    auto ref_image = Image::load_image("../../reference_images/rainbow_ball_spiral.jpg");
    std::cout << ref_image.height() << "x" << ref_image.width() << std::endl;

    save_image("ref.png", ref_image);

    ImageEvolver driver;
    driver.set_target_image(std::move(ref_image));
    driver.initialize_random_population(40, 128);

    for(int i = 0; i < 200; ++i) {
        std::cout << "=====Generation " << i << "=====" << std::endl;
        driver.advance_generation();
    }

    std::cout << driver.population().size() << std::endl;

    int i = 0;
    for(auto& state : driver.population()) {
        auto img = driver.bg_image().clone();
        driver.print_state(std::cout, state);

        driver.apply_state(state, img); 

        std::stringstream filename;
        filename << "State" << i << ".png";

        save_image(filename.str(), img);

        std::cout << "\n";
        ++i;
    }

    return 0;
}

int main(int argc, char** argv) {
    return qt_main(argc, argv);
}
