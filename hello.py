from flask import Flask
from flask import jsonify
import serial
import json
app = Flask(__name__)
ser=serial.serial_for_url(port, 115200)

INDEX_PAGE_MAX = 100

@app.route('/')
def hello_world():
	return 'Hello, World!\n'

welcome = "Welcome to 3ESE API!"

@app.route('/api/welcome/')
def api_welcome():
	return welcome

@app.route('/api/welcome/<int:index>')
def api_welcome_index(index):
	if index > INDEX_PAGE_MAX:
		return abort(404)
	return jsonify(index = index, val = welcome[index])

## Erreur

@app.errorhandler(404)
def page_not_found(error):
	return render_template('page_not_found.html'), 404

## Température

@app.route('/temp', methods = ['GET', 'POST'])
def get_temperatures():
	global temperatures
	if request.method == 'GET':
		ser.write("GET_T")
		temperatures = ser.read(4)
		temperatures.append(temperatures)
	if request.method == 'POST':
		return '', 202
	return jsonify({'Valeur des temperatures': temperatures})

@app.route('/temp/<int: index>', methods = ['GET', 'DELETE'])
def get_temperature_index(index):
	global temperatures
	if request.method == 'GET':
		return jsonify({"index": index, "Temperatures": temperatures[index]})
	if request.method == 'DELETE':
		del temperatures[index]
		return "", 200

## Pression

@app.route('/pres', methods = ['GET', 'POST'])
def get_pressures():
	global pressures
	if request.method == 'GET':
		ser.write("GET_T")
		pressures = ser.read(4)
		pressures.append(pressures)
	if request.method == 'POST':
		return '', 202
	return jsonify({'Valeur des pressions': pressures})

@app.route('/pres/<int: index>', methods = ['GET', 'DELETE'])
def get_pressure_index(index):
	global pressures
	if request.method == 'GET':
		return jsonify({"index": index, "Pression": pressures[index]})
	if request.method == 'DELETE':
		del pressures[index]
		return "", 200

## Scale

@app.route('/scale/', methods=['GET'])
def api_scale():
        global scale
        ser.write("GET_K")
        scale = ser.read(4)
        return jsonify({"scale value": scale})
