Created By Bruce Mingxin Liu
April 18th 2017


This is a inventory control for checking avaliable spaces for priority parts service and client pair. 

The client has a user input for the priority part's name in a string, and the part name is sent to the service via srv_msg part_name. 

The service listens to the logic camera and temporarily stores all the empty locations. Then service checks the potential collision, if none then the filtered locations will be sent back to the client using name.response.
# inventory_control
