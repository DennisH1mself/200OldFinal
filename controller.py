import socket
arduino_ip = "192.48.56.2" 
arduino_port = 80  
def sendToArduino(code: int):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((arduino_ip, arduino_port))
            # Send the code as an HTTP GET request
            request = f"{code}\r\n\r\n"
            s.send(request.encode())
            # Receive the response (optional)
            response = s.recv(1024)
            print("Response from Arduino:", response.decode())
    except Exception as e:
        print("Error:", e)
# sendToArduino(155)  # test if the function works
while True:
    code = input("Enter code: ")
    if code == "exit":
        break
    sendToArduino(int(code))