import socket
import requests
arduino_ip = "192.48.56.2"
arduino_port = 80
arduino_url = f"http://{arduino_ip}:{arduino_port}/"

def sendToArduino(code: int):
    try:
        response = requests.post(arduino_url, json={'key': 'value'}, params={'param_example': 'ppff'}) #requests.get(arduino_url, headers={"codexxx": str(code)}, timeout=5, params={"code": str(code)})
        response.raise_for_status()
        
        print("Status Code:", response.status_code)
        print("Response Text:", response.json())
    except Exception as e:
        print("Error:", e)
while True:
    code = input("Enter code: ")
    if code == "exit":
        break
    sendToArduino(int(code))