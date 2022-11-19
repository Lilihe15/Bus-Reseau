from flask import Flask
from flask import jsonify
import json
app = Flask(__name__)

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

@app.errorhandler(404)
def page_not_found(error):
	return render_template('page_not_found.html'), 404
