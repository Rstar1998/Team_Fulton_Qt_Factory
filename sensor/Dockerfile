FROM python:3.9-slim

# Set working directory
WORKDIR /app

# Copy application code into the container
COPY . /app

# Install dependencies
RUN pip install -r requirements.txt

# Command to run the Python script
CMD ["python", "main.py"]
