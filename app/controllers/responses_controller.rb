class ResponsesController < ApplicationController
    
    def new
        @response=Response.new
        @request=Request.find(params[:r_id])
    end
    
    def create
        @request=Request.find(params[:response][:r_id])
        @response=@request.responses.build(params.require(:response).permit(:name,:contact,:content))
        if @response.save
            redirect_to root_path
        else
            render new
        end
    end
    
    def show
        @response=Response.find(params[:id])
        @request=@response.request
    end
    
    def index
        @requests=Request.all
    end
    
    def auto
        print "======================="
        print "enter auto"
        print "==============================="
        @request=Request.find(params[:r_id])
        @response=@request.responses.build(name:"autofill-name",contact:"autofill-contact",content:"autofill-content")
        if @response.save
            redirect_to root_path
        else
            render new
        end
    end
end
