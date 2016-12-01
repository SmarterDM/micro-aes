import sys, subprocess

files = [
  ["ECBVarTxt256.rsp", "ECBVarKey256.rsp", "ECBKeySbox256.rsp"],
  ["ECBVarTxt192.rsp", "ECBVarKey192.rsp", "ECBKeySbox192.rsp"],
  ["ECBVarTxt128.rsp", "ECBVarKey128.rsp", "ECBKeySbox128.rsp"]
]

tests = 0

def test_file(file_path, size):
  global tests

  with open(file_path, "r") as file:
    lines = file.readlines()

  decrypt = 0
  key = None
  plainText = None
  cipherText = None

  for line in lines:
    if line.startswith("KEY"):
      key = line[len("KEY = "):].strip()
    elif line.startswith("PLAINTEXT"):
      plainText = line[len("PLAINTEXT = "):].strip()
    elif line.startswith("CIPHERTEXT"):
      cipherText = line[len("CIPHERTEXT = "):].strip()
    elif line.startswith("[DECRYPT]"):
      decrypt = 1

    if key != None and plainText != None and cipherText != None:
      command = "./encrypt -k " + key

      if decrypt:
        command += " -b " + cipherText + " -d"
      else:
        command += " -b " + plainText

      command += " -s " + str(size)

      output = subprocess.check_output(command, shell=True).strip()

      if decrypt:
        if output.upper() != plainText.upper():
          print "Failed decrypting " + cipherText + " to " + plainText.upper()
          print "Got: " + output.upper()
          print "Key: " + key
          sys.exit(1)
      else:
        if output.upper() != cipherText.upper():
          print "Failed encrypting " + plainText + " to " + cipherText.upper()
          print "Got: " + output.upper()
          print "Key: " + key
          sys.exit(1)

      tests = tests + 1

      key = None
      plainText = None
      cipherText = None

  # return


if __name__ == '__main__':
    test_file(files[0][0], 256)
    test_file(files[0][1], 256)
    test_file(files[0][2], 256)
    test_file(files[1][0], 192)
    test_file(files[1][1], 192)
    test_file(files[1][2], 192)
    test_file(files[2][0], 128)
    test_file(files[2][1], 128)
    test_file(files[2][2], 128)
    print "{} have passed successfully".format(tests)
