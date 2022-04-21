from flask import Flask 
from flask import render_template
import urllib.request

app = Flask(__name__)

@app.route('/')
@app.route('/index')
def index():

    
    request_url = urllib.request.urlopen('https://gutenberg.org/ebooks/search/?query=&submit_search=Go%21')
    URL = request_url.read()q
    
    return render_template('index.html', title='Welcome', code=request_url)
