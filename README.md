
# Smart Contract Donwloader

This is a tool to download the latest smart contract from  [Etherscan](https://etherscan.io/) and Convert it into .sol format. 
This is a project extending the work of [andstor](https://github.com/andstor/smart-contract-downloader).

## Features

Downloads Latest Smart Contract from Etherscan.

Converts the default source code format of Etherscan in .json to .sol files.

Fixes the solc compiler version of each contract to be data consistent.

Removes Data Incosistency to avoid any compilation Error when you use the Dataset for finding Vulnerabilities or other stuff .





## Requirements


### Installation

```bash
  git clone https://github.com/aryankaushik11/Contract_Downloader.git
  cd Contract_Downloader
```
Install Python Dependencies
```bash
  pip install -r requirements.txt
```

### Etherscan API access
In order to gain access to the Etherscan.io API, you will need an Etherscan [acount](https://docs.etherscan.io/getting-started/creating-an-account) and generate [API key(s)](https://docs.etherscan.io/getting-started/viewing-api-usage-statistics). If using [orchestration](#orchestration), the API key(s) needs to be added to the `api_keys.json` file.

### Getting a CSV File

A sample csv file is in the repository itself: [CSV](https://github.com/aryankaushik11/Contract_Downloader/blob/main/script/contract_addresses.csv) which has the most updated contract_addresses till July 2024.

In addition you can dowload the a .csv file from Etherscan OpenSource: [link](https://etherscan.io/exportData?type=open-source-contract-codes).

After Downloading the .csv file from the link you need to only keep the Contract Address Column (Delete the Column Name too)and delete everything else. Can be done easily with Microsoft Excel.

## Contracts downloader
The `contracts_downloader.py` script will try to download all the verified smart contract data from the available on [etherscan.io](https://etherscan.io), whos address is in the address list (CSV file). Each contract address will producee a JSON file with the name of the address, conttaining the data provided by Etherscan. Addresses that has not yet been verified on Etherscan will still produce an JSON file with mostly empty data fields.

### Usage

```script
usage: contracts_downloader.py [-h] [-t token] [-a addresses] [-o output] [--shard shard] [--index index] [--skip skip]

Download contracts from Etherscan.io.

optional arguments:
  -h, --help            show this help message and exit
  -t token, --token token
                        Etherscan.io API key.
  -a addresses, --addresses addresses
                        CSV file containing a list of contract addresses to download.
  -o output, --output output
                        the path where the output should be stored.
  --shard shard         the number of shards to split data in.
  --index index         the index of the shard to process. Zero indexed.
  --skip skip           the lines to skip reading from in the address list.
```

### Example
To download the smart contracts whose address is in `contract_addresses.csv`, run:
```
python script/contracts_downloader.py -t <API_KEY> -a contract_addresses.csv
```
The contracts will be saved to `./output` as default.

## Orchestration
In order to speed up the downloading process, an orchestration script is provided. This enables multithreaded downloading from Etherscan, using multiple API keys. In order for this to be effective, the contract address list needs to be split into multiple logical shards.

### Usage
```script
usage: orchestrate.py [-h] [-t tokens] [-a addresses] [-o output] --shard shard [--range start_index end_index] [--n-threads n_threads] [--skip skip] [--token-multiplier token_multiplier]

Orchistration tool for managing concurrent downloading of contracts from Etherscan.io.

optional arguments:
  -h, --help            show this help message and exit
  -t tokens, --tokens tokens
                        JSON file with Etherscan.io access tokens.
  -a addresses, --addresses addresses
                        CSV file containing a list of contract addresses to download.
  -o output, --output output
                        the path where the output should be stored.
  --shard shard         the number of shards to split data in.
  --range start_index end_index
                        the range of shards to proocess. Zero indexed.
  --n-threads n_threads
                        the n_threads to use. -1 means max.
  --skip skip           the iterations to skip at start.
  --token-multiplier token_multiplier
                        the maximum number of concurrent use of an access token.
```
### Example

To start a distributed downloading with 5 threads, each with it's own API key defined in `api_keys.json`, run:
```
python script/contracts_downloader.py --shard 5 -a contract_addresses.csv
```

To limit the number of threads, just pass the `--n-threads` argument.
```
python script/contracts_downloader.py --n-threads 2 --shard 5 --addresses contract_addresses.csv
```
This will use a maximum of two concurrent threads for downloading. If number of API keys is > `n-threads` each new shard/thread will pick the next key from the list.

## Convert the files in ./output to .sol 

This Program will convert the json file to sol files.

Change the path in convert_json_to_sol.py file to ./output or the the place where the json files are stored.

```bash
python3 convert_json_to_sol.py 
```

## Fix the contract solidity compiler  version

```bash
python3 update_pragma.py
```

## Remove all the incosistent data 

This Program removes all the incosistent data of the contracts for smooth compilation of all the tools you will use.

#### Note: You will need g++ version 11 and above

```bash
g++ remove_incosistency.cpp -o remove_incosistency

./remove_incosistency
```

👏👏👏👏 Congrats now you have the latest dataset of solidity smart contracts .


## License

©️ [aryankaushik11](https://github.com/aryankaushik11)

©️ [andstor](https://github.com/andstor/smart-contract-downloader)

[MIT](https://choosealicense.com/licenses/mit/)

