var hostParts = window.location.host.split('.');
var portalDomain = window.location.host.substr(window.location.host.split('.')[0].length + 1, window.location.host.length - window.location.host.split('.')[0].length);
var env = 'local';
var blobFolder = 'qa/';
var contentPath = '/payment/contents/';
var baseUrl = 'https://' + window.location.host + '/payment';
var absoluteBaseUrl = 'https://' + window.location.host;
var basePortalUrl = 'https://' + window.location.host;
var vendorBundleSrc = baseUrl + '/build/vendor.bundle.js?v=1.0.0.212';
var developerBundleSrc = baseUrl + '/build/app.bundle.js?v=1.0.0.212';
var plansBundleSrc = baseUrl + '/build/plans-1.0.0.212.bundle.js';
var appJsSrc = baseUrl + '/scripts/app.js?v=1.0.0.212';
var bootstrapSrc = 'styles/bootstrap/bootstrap.min.css';
var fontAwesomeSrc = 'fonts/fontawesome5-subset/css/all.min.css';
var jQuerySrc = '/blob/common/scripts/jquery-3.5.1.min.js';
var googleFontsSrc = 'https://fonts.googleapis.com/css?family=Montserrat:200,300,400,500,600,700|Source+Sans+Pro:200,300,400,600,700|Open+Sans:300,400,600,700,800|Roboto+Slab:100,300,400,700|Work+Sans:300,400,500,600,700|Merriweather:300,400,600,700';
var esShimSrc = 'scripts/es6/es6-shim.min.js';
var resFileName = 'dev.json';
var portalDomainList = { mpit: 'ilcvperfetto.it', mpes: 'micvideal.es', mpfr: 'moncvparfait.fr', mpbr: 'meucurriculoperfeito.com.br', mpuk: 'myperfectcv.co.uk' };
var mainCssSrc = baseUrl + '/stylesheets/@@portalStyleDir/main.css?v=1.0.0.212';
var domain, imgDir, styleSheetDir, jsonFileDir;


if (window.location.host.split('.').length > 2) {
    domain = window.location.host.split(':')[0].substr(window.location.host.indexOf('.') + 1);
} else {
    domain = window.location.host;
}

switch (hostParts[0]) {
case 'reg':
case 'reg-app':
case 'pen':
    env = hostParts[0];
    blobFolder = 'reg/';
    resFileName = 'reg.json';
    break;
case 'stg':
case 'stg-app':
    env = 'stg';
    blobFolder = 'stg/';
    resFileName = 'stg.json';
    break;
case 'qa':
case 'qa-app':
    env = hostParts[0];
    blobFolder = 'qa/';
    break;
case 'perf':
case 'perf-app':
    env = hostParts[0];
    blobFolder = 'perf/';
    break;
case 'www':
    env = hostParts[0];
    blobFolder = 'prod/';
    resFileName = 'prod.json';
    break;
}

var ecomJsonPath = baseUrl + '/contents/' + blobFolder + 'common/localizedText.json?v=1.0.0.212';
var ecomHostName = window.location.hostname.substring(window.location.hostname.indexOf('.') + 1);
var localisedTextJsonPath = baseUrl + '/contents/' + blobFolder + ecomHostName + '/localizedText.json?v=1.0.0.212';
var resfilePath = baseUrl.replace('@@env', env) + '/contents/' + blobFolder + ecomHostName + '/' + resFileName + '?v=1.0.0.212';
var nrJsPath = baseUrl.replace('@@env', env) + '/contents/' + blobFolder + ecomHostName + '/nr.js';

function setBuildJsDirectory(localizedPath) {
    mainCssSrc = mainCssSrc.replace('payment', localizedPath);
}

function setContentDirectory(domain) {
    switch (domain) {
    case portalDomainList['mpit']:
        jsonFileDir = styleSheetDir = imgDir = 'mit';
        setBuildJsDirectory('pagamento');
        break;
    case portalDomainList['mpes']:
        jsonFileDir = styleSheetDir = imgDir = 'mes';
        setBuildJsDirectory('pago');
        break;
    case portalDomainList['mpfr']:
        jsonFileDir = styleSheetDir = imgDir = 'mfr';
        setBuildJsDirectory('paiement');
        break;
    case portalDomainList['mpbr']:
        jsonFileDir = styleSheetDir = imgDir = 'mbr';
        setBuildJsDirectory('pagamento');
        break;
    case portalDomainList['mpuk']:
        styleSheetDir = 'muk';
        imgDir = 'mpuk';
        jsonFileDir = 'muk';
        break;
    default:
        break;
    }
}

function isEmpty(obj) {
    for (var key in obj) {
        if (obj.hasOwnProperty(key))
            return false;
    }
    return true;
}

function prefetchFiles(src, callback, attributes) {
    var s, r, t;
    r = false;
    s = document.createElement('link');
    s.rel = 'prefetch';
    s.href = src;
    if (attributes && isEmpty(attributes)) {
        for (var key in attributes) {
            var attr = document.createAttribute(key);
            if (attributes[key]) {
                attr.value = attributes[key];
            }
            s.setAttributeNode(attr);
        }
    }
    s.onload = s.onreadystatechange = function () {
        if (!r && (!this.readyState || this.readyState == 'complete' || this.readyState == 'loaded')) {
            r = true;
            callback && callback();
        }
    };
    t = document.getElementsByTagName('link')[0];
    t.parentNode.insertBefore(s, t);
}

function loadImageFiles() {
    prefetchFiles(baseUrl + '/images/mpr/logo.png');
    prefetchFiles(baseUrl + '/images/wlb/loading.gif');
    prefetchFiles(baseUrl + '/images/mpr/christopher.png');
    prefetchFiles(baseUrl + '/images/mpr/donna.png');
    prefetchFiles(baseUrl + '/images/mpr/breadcrumb-check-mpr.png');
    if (imgDir) {
        var baseImgUrl = '/images/' + imgDir + '/';
        prefetchFiles(baseUrl + baseImgUrl + 'christopher.png');
        prefetchFiles(baseUrl + baseImgUrl + 'donna.png');
        prefetchFiles(baseUrl + baseImgUrl + 'resellicons.png');
        prefetchFiles(baseUrl + baseImgUrl + 'footer-lc-logo.png');
        if (imgDir == 'mes' || imgDir == 'mmx') {
            prefetchFiles(baseUrl + baseImgUrl + 'favicon.png');
        }
        prefetchFiles(baseUrl + baseImgUrl + 'logo.svg');
    }
}

setContentDirectory(domain); //set css,styles and imageDirectory

prefetchFiles(vendorBundleSrc);		//prefetch vendor bundle
prefetchFiles(developerBundleSrc);	//prefetch developer bundle
prefetchFiles(plansBundleSrc);	//prefetch plans bundle
prefetchFiles(appJsSrc);	//prefetch app JS
prefetchFiles(contentPath + bootstrapSrc);						//prefetch bootstrap CSS
prefetchFiles(contentPath + fontAwesomeSrc);						//prefetch fontawesome CSS
prefetchFiles(jQuerySrc);						//prefetch jQuery
prefetchFiles(contentPath + esShimSrc);
prefetchFiles(googleFontsSrc);					//prefetch googleFonts CSS
prefetchFiles(mainCssSrc.replace('@@portalStyleDir', styleSheetDir));			//prefetch main CSS 
prefetchFiles(ecomJsonPath.replace('@@jsonFileDir', jsonFileDir));            //prefetch ecom JSON
prefetchFiles(localisedTextJsonPath.replace('@@jsonFileDir', jsonFileDir));   //prefetch ecom JSON (localizedText)
prefetchFiles(resfilePath);
prefetchFiles(nrJsPath);
loadImageFiles();										//prefect image files