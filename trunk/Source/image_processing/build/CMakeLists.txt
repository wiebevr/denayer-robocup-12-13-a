PROJECT( Field ) 
FIND_PACKAGE( OpenCV REQUIRED )
ADD_EXECUTABLE( ${PROJECT_NAME} ../general/main.cpp 
 								../vision_field.cpp 
								../vision_field.h 
								../public\ data/vision_data.cpp 
								../public\ data/vision_data.h 
								../Balls.cpp 
								../Balls.h 
								../DataCircle.cpp 
								../DataCircle.h 
								../Robot.cpp 
								../Robot.h 
								../vision.cpp 
								../vision.h )
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${OpenCV_LIBS} ) 
