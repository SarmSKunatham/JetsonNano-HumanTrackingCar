import jetson.inference  # module for object detection
import jetson.utils  # module for camera capture
import serial  # module for serial communication

# Serial port connection
ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
# load obj detection model with 91 classes
net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold=0.5)
# '/dev/video0' for V4L2, connecting to camera device for streaming
camera = jetson.utils.videoSource("csi://0")
# 'my_video.mp4' for file, video output interface
display = jetson.utils.videoOutput("display://0")

# video output interface with the videoOutput object and create a main loop that will run until the user exits:
while display.IsStreaming():
	img = camera.Capture()  # camera capture
	detections = net.Detect(img)  # detecting object
	for detection in detections:
	    if detection.ClassID == 1:  # pick only person
            # print(detection)
            # Center in x-axis
            center_x = 1280 / 2
            pos_x = detection.Center[0]
            area = detection.Area  # Area of bounding box
            angle_x = (detection.Center[0]/1280)*180  # Convert to degree
            angle_y = (detection.Center[1]/720)*180  # Convert to degree
            print(f"Area: {area}, Position_x: {pos_x}, Center: {center_x}, Angle_x: {angle_x}, Angle_y: {angle_y}")
            cmd = '{"area": %d,"angle_x":%d, "angle_y": %d}' % (area ,angle_x, angle_y)
            print(cmd)
            ser.write(cmd)

    display.Render(img) # visualize the result
    display.SetStatus("Object Detection | Network {:.0f} FPS".format(net.GetNetworkFPS()))

ser.close()

'''
In detection it returns:
    - Area : area of bounding box
    - Bottom : bottom bounding box coordinate
    - Center : center coordinate of the bounding box
    - ClassID : class index of the detected obj
    - Confidence : confidence value
    - Height
'''
