import RPi.GPIO as GPIO
from pathlib import Path
from PIL import Image
from pycoral.adapters import common
from pycoral.adapters import classify
from pycoral.utils.edgetpu import make_interpreter
from pycoral.utils.dataset import read_label_file

GPIO.setwarnings(False)

GPIO.setmode(GPIO.BCM)

gpio_pin0 = 4
gpio_pin1 = 17
gpio_pin2 = 22

GPIO.setup(gpio_pin0, GPIO.OUT)
GPIO.setup(gpio_pin1, GPIO.OUT)
GPIO.setup(gpio_pin2, GPIO.OUT)

GPIO.output(gpio_pin0, GPIO.LOW)
GPIO.output(gpio_pin1, GPIO.LOW)
GPIO.output(gpio_pin2, GPIO.LOW)

script_dir = Path(__file__).parent.resolve()

model_file = script_dir/'models/fire-safe-vs-sos.tflite' # name of model
data_dir = script_dir/'data'
label_file = data_dir/'safe-vs-sos.txt' # Name of your label file
image_file = data_dir/'test'/'Περιαστικό_Δάσος_Βριλησσίων_2_β.jpg' # Name of image for classification

interpreter = make_interpreter(f"{model_file}")
interpreter.allocate_tensors()

size = common.input_size(interpreter)
image = Image.open(image_file).convert('RGB').resize(size, Image.ANTIALIAS)

common.set_input(interpreter, image)
interpreter.invoke()
classes = classify.get_classes(interpreter, top_k=1)

labels = read_label_file(label_file)
for c in classes:
    print(f'{labels.get(c.id, c.id)} {c.score:.5f}')
print(c.id)

if c.id == 0:
    print ('safe')
    GPIO.output(gpio_pin0, GPIO.HIGH)
    GPIO.output(gpio_pin1, GPIO.LOW)
    GPIO.output(gpio_pin2, GPIO.LOW)
elif c.id == 1:
    print ('warning')
    GPIO.output(gpio_pin0, GPIO.LOW)
    GPIO.output(gpio_pin1, GPIO.HIGH)
    GPIO.output(gpio_pin2, GPIO.LOW)
else:
    print ('sos')
    GPIO.output(gpio_pin0, GPIO.LOW)
    GPIO.output(gpio_pin1, GPIO.LOW)
    GPIO.output(gpio_pin2, GPIO.HIGH)