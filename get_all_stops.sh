if [ -f .env ] ; then
  export $(cat .env | xargs)
fi

if [ ! -f arrets.json ] ; then
	curl "https://data.bordeaux-metropole.fr/geojson?key=$BORDEAUX_API_KEY&typename=sv_arret_p" | python -m json.tool > arrets.json
fi

cat arrets.json | jq ".features[].properties | {\"id\": .ident, \"name\": .libelle, \"vehicule\":.vehicule}"
