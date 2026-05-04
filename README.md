## README: EMG-Based Prosthetic Hand Using Neural Network

This repository contains the implementation of an intelligent, multi-channel **Electromyography (EMG)** controlled prosthetic hand. The system utilizes a **Convolutional Neural Network (CNN)** to classify muscle activity into nine distinct hand gestures, which are then executed in real-time by a 3D-printed prosthetic mechanism.

---

### ## Project Overview
The goal of this project is to develop a cost-effective and scalable assistive device for individuals with upper-limb loss. By bridging the gap between biomedical signal processing and deep learning, the system provides a more natural and intuitive control interface compared to traditional threshold-based myoelectric limbs.

**Key Features:**
*   **Multi-Channel Sensing**: Uses five **Muscle BioAmp Patchy** sensors for detailed forearm muscle activity acquisition.
*   **Deep Learning Classification**: A CNN model identifies 9 gestures with approximately **80-85% accuracy**.
*   **Real-Time Actuation**: Low-latency control of 5 high-torque **MG996R** servo motors.
*   **Tendon-Driven Design**: 3D-printed (PLA) hand using the InMoov modular design for human-like motion.

---

### ## Hardware Requirements
| Component | Specification/Function |
| :--- | :--- |
| **Microcontroller** | **Arduino Nano** (ATmega328P) |
| **EMG Sensors** | 5x **Muscle BioAmp Patchy** |
| **Actuators** | 5x **MG996R** High-Torque Servos |
| **Prosthetic Hand** | 3D-Printed PLA (Tendon-driven) |
| **Power Supply** | 7.4V Li-ion battery (for servos) + 5V USB (for logic) |

---

### ## Software Pipeline
The software architecture is divided into three primary stages:

1.  **Signal Acquisition & Preprocessing**:
    *   Analog signals are amplified and filtered (74.5 Hz to 149.5 Hz) via hardware.
    *   Digital smoothing is performed using a **Moving Average Filter**.
    *   Data is segmented using a **sliding window** (50 samples, 50% overlap).

2.  **Feature Extraction**:
    Six time-domain features are computed for each channel to represent muscle patterns:
    *   Root Mean Square (**RMS**)
    *   Mean Absolute Value (**MAV**)
    *   Waveform Length (**WL**)
    *   Zero Crossing (**ZC**)
    *   Slope Sign Change (**SSC**)
    *   Variance (**VAR**)

3.  **CNN Architecture**:
    *   **Input**: Structured $5 \times 6 \times 1$ feature matrix.
    *   **Layers**: Two Conv2D layers (32/64 filters), Batch Normalization, Max Pooling, and two Dense layers (128/64 units).
    *   **Output**: Softmax layer for 9 gesture classes.

---

### ## Supported Gestures
The system is trained to recognize and actuate the following:
*   **Open Hand / Close Hand**
*   **Individual Finger Movements** (Thumb, Index, Middle, Ring, Little)
*   **Combined Gestures**: Victory Sign, Thumbs Up

---

### ## Performance
*   **Generic Model**: ~80% accuracy (generalized across 10 users).
*   **Custom Model**: ~85% accuracy (user-specific calibration).
*   **System Stability**: Employs confidence-based filtering (threshold = 0.7) to prevent unintended activations.

---

### ## Repository Structure
*   `/arduino`: Contains firmware for EMG data streaming and servo control.
*   `/python`: Scripts for data collection, feature extraction, and CNN training.
*   `/models`: Pre-trained `.h5` model files and `scaler.pkl`.

---

### ## How to Use
1.  **Hardware Setup**: Connect sensors to A0-A4 and servos to D3, D5, D6, D9, D10.
2.  **Data Collection**: Run the Python data collection script while performing gestures to build a custom dataset.
3.  **Training**: Train the model using the provided CNN architecture script.
4.  **Inference**: Run the live classification script to control the prosthetic hand in real-time.

---

