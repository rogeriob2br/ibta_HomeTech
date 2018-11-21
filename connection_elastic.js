var elasticsearch=require('elasticsearch');

var client = new elasticsearch.Client( {  
  hosts: [
    'https://elastic:Xr75DAhrRBt0dueT5xsks2b8@6dc057d72b9b491a9b2dfee863ae06a9.europe-west1.gcp.cloud.es.io:9243/'
  ]
});

module.exports = client; 
client.ping({
    requestTimeout: 30000,
}, function(error) {
    if (error) {
        console.error('elasticsearch cluster is down!');
    } else {
        console.log('Everything is ok');
    }
});
