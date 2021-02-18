# Dynamic Camera Stabilization

The dynamic camera stabilization is based upon a visual feature matching approach.  
In this approach a keyframe gets selected and the current video feed is stabilized using this frame as a stable
reference.

---

The algorithm consists mainly of the following steps.

### 1. Feature Detection

- _FeatureDetection.hpp_
- _FeatureDetection.cpp_

### 2. Feature Matching

- _FeatureMatching.hpp_
- _FeatureMatching.cpp_

### 3. Frame Warping

- _FrameWarping.hpp_
- _FrameWarping.cpp_

### 4. Background Segmentation

- _BackgroundSegmentation.hpp_
- _BackgroundSegmentation.cpp_

### Repeat

---

### Algorithm Wrapper

The previously mentioned steps are wrapped for easier usage in:

- _DynamicStabilization.hpp_
- _DynamicStabilization.cpp_

---

# Static Calibration

The static calibration is done by pose estimation based on a minimization of the reprojection error. We use a high
definition map that contains the world positions of landmarks along the road. These landmarks are associated with pixels
in the camera feed. Based on this matching the pose estimation is performed and the camera extrinsic parameters are
estimated.

---

### Camera Pose Estimation

- _CameraPoseEstimation.hpp_
- _CameraPoseEstimation.cpp_


- _Residuals.hpp_
- _Residuals.cpp_

### Projection from World Space Landmarks to Image Space

- _RenderingPipeline.hpp_
- _RenderingPipeline.cpp_


- _WorldObjects.hpp_
- _WorldObjects.cpp_


- _Intrinsics.hpp_
- _Intrinsics.cpp_

### Data Annotation Tool to mark landmark pixels

- _Watersheder.hpp_
- _Watersheder.cpp_

---

# Other

### Calculation of Optical Flow to measure the stabilization

- _OpticalFlow.hpp_
- _OpticalFlow.cpp_

### Wrapper for CSV writing of arbitrary data

- _CSVWriter.hpp_
- _CSVWriter.cpp_

### Runtime measurement of algorithms

- _TimeMeasureable.hpp_
- _TimeMeasureable.cpp_
