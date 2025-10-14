import time, os, sys
from LIB_x86_64 import libPMUT

# Judge the length of arguments
# Set_Server_FIFO(nm)
# Connect to the Service server. Returns 1 for a successful connection; otherwise, it returns 0.
# nm is the service name (in the current version, it must be set to None to successfully connect to the Service).
if len(sys.argv) > 1:
    fifo_path = f"/tmp/{sys.argv[1]}"
    if os.path.exists(fifo_path):
        libPMUT.Set_Server_FIFO(sys.argv[1])
    else:
        print(f"Error: MUT Service FIFO Name incorrect : '{sys.argv[1]}' does not exist in /tmp directory.")
        sys.exit(1)
else:
    libPMUT.Set_Server_FIFO(None)

# Clear the screen
os.system("cls" if os.name == "nt" else "clear")

while True:
    print("===============================================================")
    print("==          MCU client demo program(Python Version)          ==")
    print("===============================================================")
    print(" 1. MCU Version")
    print(" 2. Other MCU command")
    print("")
    print(" Z. >>> Exit Program<<<")
    print("===============================================================")
    option = input("Select which function you want to do: ")
    
    if option.upper() == "Z":
        break
    elif option == "1":
        # LAUNCH_MCU_CMD(func, input)
        # A function for communicating with the Service server. Upon successful communication, it returns the result of the inquiry.
        # 'func' is the function to inquire, and 'input' is the parameter to be passed to that function.
        restList = libPMUT.LAUNCH_MCU_CMD("ST_SYSTEM_GET_01_01_MCU_VERSION", [])
        print("The MCU version is %d." % (restList[0]))
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
                
            # Execute MCU command        
            restList = libPMUT.LAUNCH_MCU_CMD(tmpCmd, dataList)
                
            if passCon != True: 
                print("The length of responsed data list is %d." % len(restList))
                print("The value of responsed data list is:")
                print(restList)
        except ValueError:
            print("Please input a legal hex value.")
        except:
            print("The unknown error occurred.")
    # Sleep & Clear the screen
    time.sleep(2)
    os.system("cls" if os.name == "nt" else "clear")
    
print("End the python program.")