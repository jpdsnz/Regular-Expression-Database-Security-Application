#!/bin/bash

echo "Testing Invalid Phone Numbers..."
./directory add "John Jones" "123"
./directory add "John Jones" "1/703/123/1234"
./directory add "John Jones" "Nr 102-123-1234"
./directory add "John Jones" "<script>alert(“XSS”)</script>"
./directory add "John Jones" "7031111234"
./directory add "John Jones" "+1234 (201) 123-1234"
./directory add "John Jones" "(001) 123-1234"
./directory add "John Jones" "+01 (703) 123-1234"
./directory add "John Jones" "(703) 123-1234 ext 204"
echo "9 Tests for phone inputs were executed.." 
