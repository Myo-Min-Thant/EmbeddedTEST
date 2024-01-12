#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "Your SSID";
const char* password = "Your Password";


String accesstoken;


void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  delay(3000);

  login();

  test1();
}


void login() {

  // Replace with your acc credentials
  String email = "your acc email";
  String pass = "your acc password";

  // Create an HTTP object
  HTTPClient http;

  // Specify the target server and resource
  String serverAddress = "http://ur_ip_address:ur_port/api/user/login";

  http.begin(serverAddress);
  String formDataBoundary = "----WebKitFormBoundary";
  String formData = "--" + formDataBoundary + "\r\n";
  formData += "Content-Disposition: form-data; name=\"email\"\r\n\r\n";
  formData += email + "\r\n";
  formData += "--" + formDataBoundary + "\r\n";
  formData += "Content-Disposition: form-data; name=\"password\"\r\n\r\n";
  formData += pass + "\r\n";
  formData += "--" + formDataBoundary + "--\r\n";

  // Set content type for form data
  http.addHeader("Content-Type", "multipart/form-data; boundary=" + formDataBoundary);

  // Send the POST request
  int httpResponseCode = http.POST(formData);

  // Check for a successful response
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    // Print the response payload
    String response = http.getString();
    Serial.println(response);

    //add
    // Parse the JSON response
    DynamicJsonDocument doc(2048);

    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.print("Error parsing JSON: ");
      Serial.println(error.c_str());
      return;
    }

    // Access the 'token' field in the 'result' object
    String token = doc["result"]["token"];

    accesstoken = token;

    // Print the token
    Serial.print("Token: ");
    Serial.println(token);
    //end



  } else {
    Serial.print("HTTP POST request failed, error: ");
    Serial.println(httpResponseCode);
  }

  // Close the connection
  http.end();


  // Wait for some time before the next iteration
  // delay(10000);
}

void test1() {
  // Replace these variables with your actual values
  String No = "02";
  String Type = "Cycle";
  String carNo = "ABC123";
  String device = "tablet";

  // Create an HTTP object
  HTTPClient http;


  // Specify the target server and resource
   String serverAddress = "http://--------------------";


  http.begin(serverAddress);

  // Set authorization header with the token
  http.addHeader("Authorization", "Bearer " + String(accesstoken));

  // Create the multipart/form-data payload
  String formDataBoundary = "----WebKitFormBoundary";
  String formData = "--" + formDataBoundary + "\r\n";
  formData += "Content-Disposition: form-data; name=\"No\"\r\n\r\n";
  formData += No + "\r\n";
  formData += "--" + formDataBoundary + "\r\n";
  formData += "Content-Disposition: form-data; name=\"Type\"\r\n\r\n";
  formData += Type + "\r\n";
  formData += "--" + formDataBoundary + "\r\n";
  formData += "Content-Disposition: form-data; name=\"carNo\"\r\n\r\n";
  formData += carNo + "\r\n";
  formData += "--" + formDataBoundary + "\r\n";
  formData += "Content-Disposition: form-data; name=\"device\"\r\n\r\n";
  formData += device + "\r\n";
  formData += "--" + formDataBoundary + "--\r\n";

  // Set content type for form data
  http.addHeader("Content-Type", "multipart/form-data; boundary=" + formDataBoundary);

  // Send the POST request
  int httpResponseCode = http.POST(formData);

  // Check for a successful response
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    // Print the response payload
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("HTTP POST request failed, error: ");
    Serial.println(httpResponseCode);
  }

  // Close the connection
  http.end();
}

void loop() {
}
