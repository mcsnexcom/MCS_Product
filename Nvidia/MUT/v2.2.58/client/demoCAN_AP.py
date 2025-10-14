import time, os, sys
from LIB_x86_64 import libPMUT

# Call Back function
# Argument "canData" is Dictionary object, the keys included as mentioned as below:
# REC_CNT        : The count of can data received from can device
# REC_ERR_CNT    : The count of can data didn't receive from can device
# AP_REC_CNT     : The count of can data received from mut server
# SND_CMD_CNT    : The count of valid can command into can device
# SND_CMD_ERR_CNT: The count of invalid can command into can device
# SND_CMD_TO_CNT : The count of can command into can device timeout
# ID             : The id of can
# RTR            : The rtr of can
# IDE            : The ide of can
# LEN            : The length of can data
# D1~D8          : The can data(1~8)
def cbFun(canData):
    #print(canData)
    print("The CAN ID: " + str(canData["ID"]))
    return 0 #success

# Judge the length of arguments
if len(sys.argv) > 1:
    libPMUT.Set_Server_FIFO(sys.argv[1])
else:
    libPMUT.Set_Server_FIFO(None)

# Clear the screen
os.system("cls" if os.name == "nt" else "clear")

while True:
    print("===============================================================")
    print("==          CAN client demo program(Python Version)          ==")
    print("===============================================================")
    print(" 1. Get F/W Version")
    print(" 2. Other CAN command")
    print(" 3. Register CAN Event")
    print(" 4. UnRegister CAN Event")
    print("")
    print(" Z. >>> Exit Program<<<")
    print("===============================================================")
    option = input("Select which function you want to do: ")
    
    if option.upper() == "Z":
        break
    elif option == "1":
        restList = libPMUT.LAUNCH_CAN_CMD("NXP_CAN_AP_02_READ_FW_VERSION", [])
        print("The F/W version is %d." % (restList[1]))
    elif option == "2":
        dataList = []
        passCon = False
        tmpCmd = input("Enter your command: ")
        try:
            while True:
                tmpVal = input("Enter your data(hex format or press enter to leave): ")
                if tmpVal == '':
                    break
                else:
                    dataList.append(int(tmpVal, 16))
                
            # Execute CAN command        
            restList = libPMUT.LAUNCH_CAN_CMD(tmpCmd, dataList)
                
            if passCon != True: 
                print("The length of responsed data list is %d." % len(restList))
                print("The value of responsed data list is:")
                print(restList)
        except ValueError:
            print("Please input a legal hex value.")
        except:
            print("The unknown error occurred.")
    elif option == "3":
        if libPMUT.Reg_CAN_CF(cbFun) == 1:
            print("Registered successfully.")
            
            EXIT_LOOP = True
            try:
                while EXIT_LOOP:
                    time.sleep(0.0001) # sleep 0.1 millisecond
            except KeyboardInterrupt as e:
                if libPMUT.UnReg_CAN() == 1:
                    print("UnRegistered successfully.")
                else:
                    print("UnRegistered failure.")
        else:
            print("Registered failure.")
    elif option == "4":
        if libPMUT.UnReg_CAN() == 1:
            print("UnRegistered successfully.")
        else:
            print("UnRegistered failure.")
            
    # Sleep & Clear the screen
    time.sleep(1)
    os.system("cls" if os.name == "nt" else "clear")
    
print("End the python program.")