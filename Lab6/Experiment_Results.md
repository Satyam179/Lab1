# Lab 6 — Experiment 7: Burp Suite analysis record

## Aim
To intercept and analyze HTTP requests and responses sent between a web browser and a local intentionally vulnerable DVWA instance, and to observe the consequences of three request manipulations.

## Tools and environment
- Windows PowerShell and Docker Desktop (Docker 29.7.2, Compose v5.4.0)
- Local DVWA application with MariaDB database, started using `docker compose up -d`
- DVWA endpoint: `http://localhost:4280`
- DVWA security level: Low
- Burp Suite Community Edition v2026.10.1 and its integrated Chromium browser
- Burp Proxy (Intercept, HTTP history) and Repeater

## Setup procedure observed
1. Cloned the upstream DVWA training repository from `https://github.com/digininja/DVWA.git`.
2. Started the local Docker Compose services; DVWA and MariaDB containers showed Started.
3. Initialized the DVWA database and logged in.
4. Selected **DVWA Security → Low**.
5. Opened DVWA in Burp's integrated browser, enabled Intercept, and observed intercepted `GET /security.php`.
6. Inspected the captured `GET` and `POST` requests in Burp Proxy → HTTP history.

## Experiment 1: Modify a hidden multipart form field

**Purpose:** Determine what happens when the client-submitted upload-size field is modified.

**Original request:**
- Endpoint: `POST /vulnerabilities/upload/`
- Multipart field: `MAX_FILE_SIZE=100000`
- Uploaded file: `test.png`
- Observed DVWA page message: `../../hackable/uploads/test.png successfully uploaded!`

**Modified request in Repeater:**
- Changed the submitted `MAX_FILE_SIZE` field to `1`; left the file data untouched.
- HTTP status: `200 OK`
- Observed page response: `Your image was not uploaded.`

**Analysis:** The modified field affected whether the file was accepted. An HTTP 200 response only indicates an HTTP response was returned; it does not mean the file was uploaded. This test alone cannot prove that an independent server-side file-size limit is implemented.

## Experiment 2: Modify a session cookie

**Purpose:** Check whether the application allows access with a changed session identifier.

**Baseline:** A valid session cookie was present on `GET /security.php`, returning authenticated DVWA Security HTML with `200 OK`.

**Modified request:**
- Set `PHPSESSID=invalidsession123` while preserving `security=low`.
- Response: `HTTP/1.1 302 Found`
- Response header: `Location: login.php`

**Analysis:** The invalid session was rejected for this protected page and the client was redirected to log in. This is evidence of session verification in the tested flow; it is not a comprehensive session-management assessment.

## Experiment 3: Modify an HTTP request header

**Purpose:** Observe whether DVWA's Security page behavior changes when the user agent is changed.

**Baseline:** `GET /security.php` with valid session returned `200 OK` and the DVWA Security HTML.

**Modified request:**
- Replaced the original `User-Agent` header with `User-Agent: Lab6-Security-Test`.
- Left valid `PHPSESSID` and `security=low` in place.
- Response: `HTTP/1.1 200 OK`
- Response body: authenticated DVWA Security page.

**Analysis:** The header change caused no visible access-control difference for this one page. This does not establish the safety or validation of other request headers.

## Overall result
All three locally authorized **HTTP** request manipulations were carried out and their observed results documented with screenshots and a PDF report prepared outside GitHub.

## Evidence checklist
The prepared seven-page report and ten redacted screenshots remain to be uploaded to the repository. Keep them under `Lab6/` alongside this file:
- `Lab6_Burp_Suite_Report.pdf`
- `01_Docker_DVWA_Startup.png`
- `02_DVWA_Security_Low.png`
- `03_Burp_HTTP_History.png`
- `04_Original_Image_Upload.png`
- `05_Original_Hidden_Field.png`
- `06_Modified_Hidden_Field.png`
- `07_Modified_Upload_Response.png`
- `08_Session_Baseline.png`
- `09_Invalid_Session_Redirect.png`
- `10_Modified_User_Agent.png`

## Outstanding requirements
The lab instructions also call for separate browser proxy configuration, Burp CA certificate installation, and HTTPS interception. The supplied screenshots and observed steps do **not** establish those tasks as completed. Additional real evidence is necessary before claiming full compliance.

## Ethics and attribution
Testing was limited to the user's own local intentionally vulnerable DVWA instance. DVWA is third-party software and is not submitted as original student source code. Session token values must be redacted from screenshots committed to public repositories.
