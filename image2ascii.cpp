#include <opencv2/opencv.hpp>


// Returns vector of string that stores ASCII lines converted from image
std::vector<std::string> image2ascii(cv::Mat image)
{
    // Grayscale string in accordance with brightness   
    const std::string gscale = "@%#*+=-:.   ";

    int gscale_len = (int)gscale.length() - 1;

    // Resize image if too big
    cv::Mat resized_image;

    if (!image.data)
    {
        std::cerr << "Unable to read Image Data." << std::endl;
    }

    int col = image.cols;
    int row = image.rows;

    if (col > 100 && col < 600) {
        resize(image, resized_image, cv::Size(), 0.2, 0.2, cv::INTER_LINEAR);
        col = resized_image.cols;
        row = resized_image.rows;
    }
    else if (col >= 500 && col <= 2000) {
        resize(image, resized_image, cv::Size(), 0.1, 0.1, cv::INTER_LINEAR);
        col = resized_image.cols;
        row = resized_image.rows;
    }
    else if (col > 2000) {
        std::cerr << "File too large to convert to ASCII Art!" << std::endl;
    }


    std::vector<std::string> lines;
    std::string line;

    // Loop over image pixel array and provide equivalent 
    // ascii character according to pixel brightness
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cv::Vec3b px = resized_image.at<cv::Vec3b>(i, j);
            uchar b = px[0];
            uchar g = px[1];
            uchar r = px[2];
            int luminence = 0.2126 * r + 0.7152 * g + 0.0722 * b;
            char ascii_char = gscale[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(gscale_len) - int((luminence * gscale_len) / 255)];
            
            line = line + ascii_char;
        }
        
        lines.push_back(line);
        line.clear();
    }

    return lines;
}