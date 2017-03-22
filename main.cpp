#include "../../../Qing/qing_common.h"
#include "../../../Qing/qing_image.h"
#include "../../../Qing/qing_converter.h"

//SIFT < $pgm_file > $key_file
// < : cin re-direction
// > : cout re-direction
// readme: Size is the region around a point of interest that is used to form the description of the keypoint.
// The larger it is the more regional information is used to describe your featurepoint. also known as scale.
// As to the response, this defines how strong a keypoint is according to the formulae described by the technique.
// The higher the value, the more likely the feature will be recognized among several instances of an object.
int main(int argc, char * argv[]) {

    //read image from ios stream
    Mat img;
    qing_load_image(cin, CV_LOAD_IMAGE_UNCHANGED, img);


    cv::SiftFeatureDetector detector;
    vector<cv::KeyPoint> sift_keypts(0);
    detector.detect(img, sift_keypts);
   // cout << sift_keypts.size() << " keypoints.." << endl;

    cv::SiftDescriptorExtractor descriptor;
    cv::Mat sift_descriptor;
    descriptor.compute(img, sift_keypts, sift_descriptor);

    int sz = sift_descriptor.size().height;
    int dimension = sift_descriptor.size().width;
    //int type = sift_descriptor.type();
    //cout << type << endl;


    cout << sz << ' ' << dimension  << endl;
    //sift out format
    //4 floating point numbers giving subpixel row and column location, scale, and orientation (in radians from -PI to PI)
    for(int j = 0; j < sz; ++j) {
        cv::KeyPoint pt = sift_keypts[j];
        cout << pt.pt.x << ' ' << pt.pt.y << ' ' << pt.size << ' ' << qing_angle_to_pi(pt.angle) << endl;
        float * ptr = sift_descriptor.ptr<float>(j);
        for(int i = 0; i < dimension; ++i) {
            cout << ptr[i] ;
            if( (i && i%20==0) || i == dimension-1) cout << endl;
            else cout << ' ';
        }
    }


# if 0
    Mat out_img;
    cv::drawKeypoints(img, sift_keypts, out_img, Scalar(0,0,255));
    imshow("sift", out_img);
    waitKey(0);
    destroyWindow("sift");
# endif

    return 1;
}
