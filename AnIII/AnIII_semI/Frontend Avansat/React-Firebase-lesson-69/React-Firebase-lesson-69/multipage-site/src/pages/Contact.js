import { useLocation } from "react-router-dom"

export default function Contact() {
    const queryString = useLocation().search;
    console.log(queryString);

    const queryParams = new URLSearchParams(queryString);

    const name = queryParams.get("name")

    return (
        <div>
            <h2>Hei {name}, contact us here...</h2>
            <p>Id sint ad adipisicing in quis. Officia duis enim irure velit veniam ex cillum sint dolor sint. 
                Cupidatat qui mollit dolor culpa adipisicing sunt in quis non ad. 
                Pariatur sint et amet esse laboris laborum adipisicing occaecat esse in in magna veniam. 
                Culpa mollit occaecat amet ut nisi culpa adipisicing ex aute id. Exercitation ea fugiat consectetur eiusmod. 
                Commodo tempor adipisicing duis minim laboris pariatur occaecat.
            </p>
        </div>
    )
}
