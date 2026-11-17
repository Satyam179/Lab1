# Lab 6 – HTTP Request/Response Interception and Manipulation (Exp 7)

**Target:** DVWA (local intentionally vulnerable application), `http://localhost:4280`  
**Tools:** Windows PowerShell, Docker Desktop, MariaDB, Burp Suite Community Edition v2026.10.1, Burp's integrated Chromium browser  
**Date of exercises:** 17 November 2026

## Aim

Conduct dynamic web application analysis by intercepting and comparing HTTP requests and responses through Burp Suite, changing a hidden form field, a session cookie, and an HTTP header.

## Observed work

1. **Hidden form field:** On `POST /vulnerabilities/upload/`, changed multipart `MAX_FILE_SIZE` from `100000` to `1`. The original `test.png` upload succeeded; the modified request returned `200 OK` with the page message **"Your image was not uploaded."**
2. **Session cookie:** On `GET /security.php`, changed a valid `PHPSESSID` to `invalidsession123` while keeping `security=low`. DVWA returned `302 Found` with `Location: login.php`.
3. **Request header:** On `GET /security.php`, changed `User-Agent` to `Lab6-Security-Test` with a valid session cookie. DVWA returned `200 OK` with the authenticated Security page.

See [Experiment_Results.md](Experiment_Results.md) for procedure, request/response observations, and limitations.

## Evidence files prepared separately

The following **locally prepared files are not yet uploaded to this GitHub folder**:
- `Lab6_Burp_Suite_Report.pdf` (seven-page PDF report)
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

Screenshots prepared for publication have session identifiers redacted.

## Important limitations

These observations were made with **HTTP** traffic in Burp's built-in browser. There is **no evidence yet** of setting up a separate browser's manual proxy, installing the Burp CA certificate in that browser, or intercepting **HTTPS** traffic. These remain outstanding parts of the lab requirements.

This lab did not require original application source code; DVWA is a third-party learning application. The report and notes document student-observed experiments rather than claiming ownership of DVWA source.
