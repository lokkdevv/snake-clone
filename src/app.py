import pyautogui
import random
import time
import string

def generate_gibberish(length=10):
    """Generate random gibberish text"""
    characters = string.ascii_letters + string.digits + string.punctuation + " "
    return ''.join(random.choice(characters) for _ in range(length))

def type_gibberish():
    """Continuously type gibberish into VS Code"""
    print("Starting gibberish typing in 3 seconds... Switch to VS Code!")
    time.sleep(3)
    
    try:
        while True:
            # Generate and type gibberish
            gibberish = generate_gibberish(random.randint(5, 50))
            pyautogui.write(gibberish, interval=0.05)
            
            # Occasionally press enter for new lines
            if random.random() < 0.3:
                pyautogui.press('enter')
            
            # Small delay between typing sessions
            time.sleep(random.uniform(0.1, 0.5))
            
    except KeyboardInterrupt:
        print("\nStopped gibberish typing")

if __name__ == "__main__":
    # Install required package if not already installed
    try:
        import pyautogui
    except ImportError:
        print("Installing pyautogui...")
        import subprocess
        subprocess.check_call(["pip", "install", "pyautogui"])
        import pyautogui
    
    type_gibberish()