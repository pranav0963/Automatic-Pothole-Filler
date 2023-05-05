import cv2
import numpy as np

# Load the video file
cap = cv2.VideoCapture('pothole.webm')

# Define the codec and create VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('pothole_detection2.avi', fourcc, 20.0, (640, 480))

# Load the trained classifier
cascade_classifier = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

while True:
    # Read a frame from the video
    ret, frame = cap.read()

    if ret:
        # Convert the frame to grayscale
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Detect potholes using the classifier
        potholes = cascade_classifier.detectMultiScale(gray, scaleFactor=1.2, minNeighbors=5)

        # Draw rectangles around the potholes
        for (x, y, w, h) in potholes:
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)

        # Display the resulting frame
        cv2.imshow('Pothole Detection', frame)

        # Write the frame to the output video file
        out.write(frame)

        # Exit if 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    else:
        break

# Release everything when done
cap.release()
out.release()
cv2.destroyAllWindows()