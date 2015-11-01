#ifndef BLURFILTER_H
#define BLURFILTER_H
#include "Filter.h"
#include "opencv2/imgproc.hpp"

/**
 * THe filter used for bluring images
 * Note: some bluring processes takes a long time
 * A max blur value is set to reduce processing time
 *
 * Implemented are normal blur (normalized box filter),
 * gassian blur, median blur, and bilateral blur
 */
class BlurFilter : public Filter
{
public:
    /**
     * The blur filter
     * Set which blur to use with _mode_
     * Set the intensity of the blur with _inten_
     * If _mode_ is invalid, it defaults to normal blur (0)
     * @param mode = which blur to use;
     *          0 = normal blur (normalized box filter)
     *          1 = gaussian blur
     *          2 = median blur (best for binary images)
     *          3 = bilateral blur (very slow)
     * @param intensity = intensity of the blur (from 0.0 to 1.0)
     */
    BlurFilter(int mode, float intensity);

    /**
     * Filters the passed in image using the preset mode
     * @param data
     * @return 0 if successful
     */
    bool filter(Data *data);

    /**
     * Used for internal testing
     * Does the same thing as filter using _data_
     */
    cv::Mat filter(cv::Mat img);

    /**
     * Sets which blur to use for filter
     * @param mode: 0 = normal blur (normalized box filter)
     *              1 = gaussian blur
     *              2 = median blur (best for binary images)
     *              3 = bilateral blur (very slow)
     */
    void setMode(int mode);

    /**
     * Sets the intensity of the blur
     * The intensity is a float from 0.0 to 1.0, where 0.0 is 0% and 1.0 is 100%
     * @param inten = float from 0.0 to 1.0
     */
    void setIntensity(float inten);

private:
    int mode;
    float intensity;

    //max blur constants for each type of blur
    const int BLURMAX = 5;
    const int GAUSMAX = 9;
    const int MEDIMAX = 201;
    const int BILAMAX = 21;
};

#endif // BLURFILTER_H
