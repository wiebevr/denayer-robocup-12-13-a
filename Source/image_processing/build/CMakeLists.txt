PROJECT( Overseer ) 
FIND_PACKAGE( OpenCV REQUIRED )
ADD_EXECUTABLE( ${PROJECT_NAME} ../general/main.cpp 
 								../vision_field.cpp 
								../vision_field.h 
								../public\ data/vision_data.cpp 
								../public\ data/vision_data.h 
								../vision_balls.cpp 
								../vision_balls.h 
								../vision_DataCircle.cpp 
								../vision_DataCircle.h 
								../vision_robot.cpp 
								../vision_robot.h 
								../vision.cpp 
								../vision.h )
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${OpenCV_LIBS} ) 


